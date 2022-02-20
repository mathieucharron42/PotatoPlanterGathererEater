#include "PotatoGameMode.h"

#include "PotatoEaterCharacter.h"
#include "PotatoGameRole.h"
#include "PotatoGameState.h"
#include "PotatoPlayerState.h"

#include "Algo/AllOf.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

void APotatoGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void APotatoGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	for (const TSubclassOf<UPotatoGameRole> roleType : _rolesTypes)
	{
		UPotatoGameRole* role = roleType->GetDefaultObject<UPotatoGameRole>();
		_roles.Add(role);
	}
}

void APotatoGameMode::RestartPlayer(AController* NewPlayer)
{
	if (NewPlayer->IsA<APotatoPlayerController>())
	{
		APotatoPlayerController* potatoPlayerController = Cast<APotatoPlayerController>(NewPlayer);
		ensure(ChangeRole(potatoPlayerController));
	}
	else
	{
		Super::RestartPlayer(NewPlayer);
	}
}

void APotatoGameMode::CheckGameEnded()
{
	UWorld* world = GetWorld();

	TArray<APotatoEaterCharacter*> potatoEaters;
	for (TActorIterator<APotatoEaterCharacter> it(world); it; ++it)
	{
		potatoEaters.Add(*it);
	}

	const bool arePotatoEatersWellFeed = Algo::AllOf(potatoEaters, [](APotatoEaterCharacter* potatoEater)
	{
		return !potatoEater->IsHungry();
	});

	if (potatoEaters.Num() > 0 && arePotatoEatersWellFeed)
	{
		APotatoGameState* gameState = GetGameState<APotatoGameState>();
		if (ensure(IsValid(gameState)))
		{
			gameState->SetGameEnded(true);
		}
	}
}

APotatoBaseCharacter* APotatoGameMode::FindSuitableCharacter(const TSubclassOf<APotatoBaseCharacter>& type)
{
	UWorld* world = GetWorld();

	APotatoBaseCharacter* suitableCharacter = nullptr;
	for (TActorIterator<APotatoBaseCharacter> it(world); it && !IsValid(suitableCharacter); ++it)
	{
		APotatoBaseCharacter* character = Cast<APotatoBaseCharacter>(*it);
		if (IsSuitableCharacter(type, character))
		{
			suitableCharacter = character;
		}
	}

	return suitableCharacter;
}

bool APotatoGameMode::IsSuitableCharacter(const TSubclassOf<APotatoBaseCharacter>& type, const APotatoBaseCharacter* character)
{
	bool suitable = false;
	if (ensure(IsValid(character)))
	{
		if (character->IsA(type))
		{
			const APotatoPlayerController* controller = character->GetController<APotatoPlayerController>();
			const bool isCharacterPossessed = IsValid(controller);
			suitable = !isCharacterPossessed;
		}
	}
	return suitable;
}


UPotatoGameRole* APotatoGameMode::GetNextRole(UPotatoGameRole* current)
{
	UPotatoGameRole* nextRole = nullptr;
	if (ensure(_roles.Num() > 0))
	{
		const int32 currentIndex = _roles.Find(current);
		const int32 nextIndex = (currentIndex + 1) % +_roles.Num();
		nextRole = _roles[nextIndex];
	}
	return nextRole;
}

void APotatoGameMode::Tick(float dt)
{
	Super::Tick(dt);

	CheckGameEnded();
}

bool APotatoGameMode::ChangeRole(APotatoPlayerController* playerController)
{
	bool success = false;

	APotatoPlayerState* playerState = playerController->GetPlayerState<APotatoPlayerState>();

	UPotatoGameRole* initialRole = playerState->GetCurrentRole();
	UPotatoGameRole* nextRole = GetNextRole(playerState->GetCurrentRole());
	TArray<UPotatoGameRole*> consideredRoles;
	while (!success && initialRole != nextRole && consideredRoles.Num() < _roles.Num())
	{
		UPotatoGameRole* role = nextRole; 
		if (ensure(IsValid(role)))
		{
			APotatoBaseCharacter* character = FindSuitableCharacter(role->CharacterType);
			if (IsValid(character))
			{
				playerController->Possess(character);
				playerState->SetCurrentRole(role);
				success = true;
			}
		}
		consideredRoles.Add(role);
		nextRole = GetNextRole(nextRole);
	}

	return success;
}

void APotatoGameMode::SpawnPotato(const FTransform& transform, const FVector& velocity)
{
	UWorld* world = GetWorld();
	if (ensure(IsValid(world)))
	{
		APotatoGameMode* potatoGameMode = world->GetAuthGameMode<APotatoGameMode>();
		if (ensure(IsValid(potatoGameMode)))
		{
			if(ensure(_potatoTypes.Num() > 0))
			{
				const TSubclassOf<APotato>& potatoType = _potatoTypes[FMath::RandRange(0, _potatoTypes.Num() - 1)];

				APotato* newPotato = world->SpawnActor<APotato>(potatoType, transform);
				UPrimitiveComponent* potatoPrimitiveComponent = Cast<UPrimitiveComponent>(newPotato->GetRootComponent());
				potatoPrimitiveComponent->SetPhysicsLinearVelocity(velocity);
			}
		}
	}
}
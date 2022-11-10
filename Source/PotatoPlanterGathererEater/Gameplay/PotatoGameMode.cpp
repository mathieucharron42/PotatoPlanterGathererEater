#include "PotatoGameMode.h"

#include "PotatoPlanterGathererEater/Characters/PotatoEaterCharacter.h"
#include "PotatoPlanterGathererEater/Characters/PotatoEatingComponent.h"
#include "PotatoPlanterGathererEater/Crops/Potato.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoGameRole.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoGameState.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoPlayerState.h"
#include "PotatoPlanterGathererEater/Utils/PotatoUtilities.h"

#include "Algo/AllOf.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

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
	if (ensure(IsValid(world)))
	{
		TArray<UPotatoEatingComponent*> eatingComponents;
		for (TActorIterator<APotatoBaseCharacter> it(world); it; ++it)
		{
			AActor* actor = *it;
			if (IsValid(actor))
			{
				UPotatoEatingComponent* component = it->FindComponentByClass<UPotatoEatingComponent>();
				if (IsValid(component))
				{
					eatingComponents.Add(component);
				}
			}
		}

		const bool arePotatoEatersWellFeed = Algo::AllOf(eatingComponents, [](UPotatoEatingComponent* eatingComponent)
		{
			return !eatingComponent->IsHungry();
		});

		if (eatingComponents.Num() > 0 && arePotatoEatersWellFeed)
		{
			APotatoGameState* gameState = GetGameState<APotatoGameState>();
			if (ensure(IsValid(gameState)))
			{
				gameState->SetGameEnded(true);
			}
		}
	}
}

APotatoBaseCharacter* APotatoGameMode::FindSuitableCharacter(const TSubclassOf<APotatoBaseCharacter>& type)
{
	APotatoBaseCharacter* suitableCharacter = nullptr;
	UWorld* world = GetWorld();
	if(ensure(IsValid(world)))
	{
		for (TActorIterator<APotatoBaseCharacter> it(world); it && !IsValid(suitableCharacter); ++it)
		{
			APotatoBaseCharacter* character = Cast<APotatoBaseCharacter>(*it);
			if (IsSuitableCharacter(type, character))
			{
				suitableCharacter = character;
			}
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
			const APotatoPlayerController* possessingController = character->GetController<APotatoPlayerController>();
			const bool isCharacterPossessed = IsValid(possessingController);
			suitable = !isCharacterPossessed;
		}
	}
	return suitable;
}

FPotatoGameRole APotatoGameMode::GetNextRole(FPotatoGameRole current)
{
	FPotatoGameRole nextRole;
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
	bool found = false;
	TArray<FPotatoGameRole> consideredRoles;

	APotatoPlayerState* playerState = playerController->GetPlayerState<APotatoPlayerState>();
	FPotatoGameRole initialRole = playerState->GetCurrentRole();

	for (FPotatoGameRole role = GetNextRole(initialRole); initialRole != role; role = GetNextRole(role))
	{
		APotatoBaseCharacter* character = FindSuitableCharacter(role.GetCharacterType());
		if (IsValid(character))
		{
			playerController->Possess(character);
			playerState->SetCurrentRole(role);
			found = true;
			break;
		}
	}

	return found;
}

void APotatoGameMode::SpawnPotato(const FTransform& transform, const FVector& velocity)
{
	UE_LOG(LogPotatoGame, Log, TEXT("Spawning potato at %s with velocity %s"), *transform.ToString(), *velocity.ToString())
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

				UE_LOG(LogPotatoGame, Log, TEXT("Spawned potato of type %s"), *potatoType->GetName())
			}
		}
	}
}
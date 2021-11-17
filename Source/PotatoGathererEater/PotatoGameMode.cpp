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
	for (const TSubclassOf<UPotatoGameRole> roleType : _rolesTypes)
	{
		UPotatoGameRole* role = roleType->GetDefaultObject<UPotatoGameRole>();
		_roles.Add(role);
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

	bool arePotatoEatersWellFeed = Algo::AllOf(potatoEaters, [](APotatoEaterCharacter* potatoEater)
	{
		return !potatoEater->IsHungry();
	});

	if (potatoEaters.Num() > 0 && arePotatoEatersWellFeed)
	{
		APotatoGameState* gameState = GetGameState<APotatoGameState>();
		gameState->SetGameEnded(true);
	}
}

APotatoBaseCharacter* APotatoGameMode::FindSuitableCharacter(const TSubclassOf<APotatoBaseCharacter>& type)
{
	UWorld* world = GetWorld();

	TArray<APotatoBaseCharacter> characters;

	for (TActorIterator<APotatoBaseCharacter> it(world, type); it; ++it)
	{
		APotatoBaseCharacter* character = Cast<APotatoBaseCharacter>(*it);
		return character;
	}

	return nullptr;
}

UPotatoGameRole* APotatoGameMode::GetNextRole(UPotatoGameRole* current)
{
	const int32 currentIndex = _roles.Find(current);
	const int32 nextIndex = (currentIndex + 1) % + _roles.Num();
	return _roles[nextIndex];
}

void APotatoGameMode::Tick(float dt)
{
	Super::Tick(dt);

	CheckGameEnded();
}

bool APotatoGameMode::ChangeRole(APotatoPlayerController* playerController)
{
	APotatoPlayerState* playerState = playerController->GetPlayerState<APotatoPlayerState>();
	UPotatoGameRole* role = GetNextRole(playerState->GetCurrentRole());
	while (role != playerState->GetCurrentRole())
	{
		APotatoBaseCharacter* character = FindSuitableCharacter(role->CharacterType);
		if (IsValid(character))
		{
			playerController->Possess(character);
			playerState->SetCurrentRole(role);
			return true;
		}

		role = GetNextRole(playerState->GetCurrentRole());
	}
	return false;
}
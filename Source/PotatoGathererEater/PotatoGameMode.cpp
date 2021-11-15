#include "PotatoGameMode.h"
#include "PotatoGameRole.h"
#include "PotatoPlayerState.h"

#include "EngineUtils.h"


void APotatoGameMode::BeginPlay()
{
	for (const TSubclassOf<UPotatoGameRole> roleType : _rolesTypes)
	{
		UPotatoGameRole* role = roleType->GetDefaultObject<UPotatoGameRole>();
		_roles.Add(role);
	}
}

APotatoBaseCharacter* APotatoGameMode::FindSuitableCharacter(const TSubclassOf<APotatoBaseCharacter>& type)
{
	UWorld* world = GetWorld();

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
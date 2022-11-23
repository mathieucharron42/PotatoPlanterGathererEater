#include "PotatoPlayerController.h"

#include "PotatoPlanterGathererEater/Gameplay/PotatoGameMode.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoCheatManager.h"

#include "EngineUtils.h"

APotatoPlayerController::APotatoPlayerController()
{
	CheatClass = UPotatoCheatManager::StaticClass();
}

void APotatoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Switch", IE_Pressed, this, &APotatoPlayerController::Authority_ChangeRole);
	InputComponent->BindAction("Quit", IE_Pressed, this, &APotatoPlayerController::Authority_QuitGame);
}

void APotatoPlayerController::Authority_QuitGame()
{
	if (ensure(HasAuthority()))
	{
		UWorld* world = GetWorld();
		if (ensure(IsValid(world)))
		{
			APotatoGameMode* gameMode = world->GetAuthGameMode<APotatoGameMode>();
			if (ensure(IsValid(gameMode)))
			{
				gameMode->QuitGame(this);
			}
		}
	}
}

void APotatoPlayerController::Authority_ChangeRole()
{
	if(ensure(HasAuthority()))
	{
		UWorld* world = GetWorld();
		if(ensure(IsValid(world)))
		{
			APotatoGameMode* gameMode = world->GetAuthGameMode<APotatoGameMode>();
			if (ensure(IsValid(gameMode)))
			{
				gameMode->ChangeRole(this);
			}
		}
	}
}

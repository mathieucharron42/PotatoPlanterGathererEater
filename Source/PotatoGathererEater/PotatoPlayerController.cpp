#include "PotatoPlayerController.h"

#include "EngineUtils.h"
#include "PotatoGameMode.h"

void APotatoPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		Authority_ChangeRole();
	}
}

void APotatoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Switch", IE_Pressed, this, &APotatoPlayerController::Server_ChangeRole);
	InputComponent->BindAction("Quit", IE_Pressed, this, &APotatoPlayerController::QuitGame);
}

void APotatoPlayerController::QuitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}

void APotatoPlayerController::Server_ChangeRole_Implementation()
{
	Authority_ChangeRole();
}

bool APotatoPlayerController::Server_ChangeRole_Validate()
{
	return true;
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

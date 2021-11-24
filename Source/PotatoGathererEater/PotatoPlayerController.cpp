#include "PotatoPlayerController.h"

#include "EngineUtils.h"
#include "PotatoGameMode.h"

void APotatoPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ChangeRole();
}

void APotatoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Switch", IE_Pressed, this, &APotatoPlayerController::ChangeRole);
}

void APotatoPlayerController::ChangeRole()
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

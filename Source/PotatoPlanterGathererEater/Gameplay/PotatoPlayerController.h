#pragma once

#include "PotatoPlanterGathererEater/Characters/PotatoBaseCharacter.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoGameRole.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PotatoPlayerController.generated.h"

UCLASS()
class POTATOPLANTERGATHEREREATER_API APotatoPlayerController : public APlayerController
{
	GENERATED_BODY()

	APotatoPlayerController();

	virtual void BeginPlay() override;

private:
	virtual void SetupInputComponent() override;

	void QuitGame();

	UFUNCTION(Server, Reliable)
	void Server_ChangeRole();

	void Authority_ChangeRole();
};

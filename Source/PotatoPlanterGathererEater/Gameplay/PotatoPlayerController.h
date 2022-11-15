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

public:
	UFUNCTION(Server, Reliable)
	void Server_ChangeRole();

	void Authority_ChangeRole();

protected:
	virtual void SetupInputComponent() override;

private:
	void QuitGame();
};

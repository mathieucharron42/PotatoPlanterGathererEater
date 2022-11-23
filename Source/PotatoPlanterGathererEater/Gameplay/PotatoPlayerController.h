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
	void Authority_ChangeRole();

protected:
	virtual void SetupInputComponent() override;

private:
	void Authority_QuitGame();
};

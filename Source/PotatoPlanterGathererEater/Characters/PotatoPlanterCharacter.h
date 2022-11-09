#pragma once

#include "PotatoPlanterGathererEater/Characters/PotatoBaseCharacter.h"
#include "PotatoPlanterGathererEater/Crops/Potato.h"

#include "CoreMinimal.h"

#include "PotatoPlanterCharacter.generated.h"

class UPotatoPlantingComponent;

UCLASS(Abstract)
class POTATOPLANTERGATHEREREATER_API APotatoPlanterCharacter : public APotatoBaseCharacter
{
	GENERATED_BODY()

public:
	APotatoPlanterCharacter();

private:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	UPotatoPlantingComponent* _potatoPlantingComponent;
};

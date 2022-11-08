#pragma once


#include "PotatoPlanterGathererEater/Crops/Potato.h"
#include "PotatoPlanterGathererEater/Characters/PotatoBaseCharacter.h"

#include "CoreMinimal.h"

#include "PotatoGathererCharacter.generated.h"

class UPotatoPickUpComponent;

UCLASS(Abstract)
class POTATOPLANTERGATHEREREATER_API APotatoGathererCharacter : public APotatoBaseCharacter
{
	GENERATED_BODY()
public:
	APotatoGathererCharacter();
	
	bool IsHoldingPotato() const;

protected:
	virtual void BeginPlay() override;

private:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	UPotatoPickUpComponent* _potatoPickUpComponent = nullptr;
};

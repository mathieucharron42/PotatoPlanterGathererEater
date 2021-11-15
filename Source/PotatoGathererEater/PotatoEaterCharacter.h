#pragma once

#include "Potato.h"
#include "PotatoBaseCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"

#include "PotatoEaterCharacter.generated.h"

UCLASS()
class POTATOGATHEREREATER_API APotatoEaterCharacter : public APotatoBaseCharacter
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;

	void UpdateVisual();

	void EatPotato(APotato* potato);

	void SetScale(float scale);

	USpringArmComponent* _springArmComponent;

	UPROPERTY(Transient)
	int32 _initialSpringArmLenght;

	UPROPERTY(Transient)
	float _scale;

	UPROPERTY(Transient)
	int32 _amountEaten;
};

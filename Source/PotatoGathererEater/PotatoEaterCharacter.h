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

public:
	bool IsHungry() const;

protected:
	UFUNCTION(BlueprintNativeEvent)
	void SetScale(float scale);
	
private:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;
	virtual void Tick(float dt);

	void UpdateVisual();
	void EatPotato(APotato* potato);

	UPROPERTY(EditAnywhere)
	float _caloryScale;

	UPROPERTY(EditAnywhere)
	float _caloriesNeeded;

	UPROPERTY(Transient)
	int32 _initialSpringArmLenght;

	UPROPERTY(Transient)
	USpringArmComponent* _springArmComponent;

	UPROPERTY(Transient)
	float _caloriesEaten;
};

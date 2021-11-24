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
	float GetCaloriesNeeded() const;
	float GetCaloriesEaten() const;

protected:
	UFUNCTION(Client, NetMulticast, Reliable)
	void Client_Multicast_SetScale(float scale);

	UFUNCTION(BlueprintNativeEvent)
	void Local_SetScale(float scale);
	
private:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* otherActor) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void Authority_UpdateVisual();
	void Authority_EatPotato(APotato* potato);

	UPROPERTY(EditAnywhere)
	float _caloryScale;

	UPROPERTY(EditAnywhere)
	float _caloriesNeeded;

	UPROPERTY(Transient)
	int32 _initialSpringArmLenght;

	UPROPERTY(Transient)
	USpringArmComponent* _springArmComponent;

	UPROPERTY(Transient, Replicated)
	float _caloriesEaten;
};

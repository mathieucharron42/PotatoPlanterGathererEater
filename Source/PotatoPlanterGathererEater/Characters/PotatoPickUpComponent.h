#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "PotatoPickUpComponent.generated.h"

class APotato;
class UInputComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTATOPLANTERGATHEREREATER_API UPotatoPickUpComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UPotatoPickUpComponent();

	bool IsHoldingPotato() const;

	void Authority_PickupPotato(APotato* potato);

	void Authority_DropPotato();

	APotato* Authority_ReleasePotato();

protected:
	virtual void InitializeComponent() override;

	virtual void UninitializeComponent() override;

private:
	UFUNCTION()
	void OnOwnerOverlap(AActor* owningActor, AActor* otherActor);
	
	UFUNCTION()
	void OnOwnerHit(AActor* owningActor, AActor* otherActor, FVector normalImpulse, const FHitResult& hit);

	void OnSetupPlayerInput(UInputComponent* inputComponent);

	UFUNCTION()
	void OnRep_HeldPotato(APotato* old);

	void SetHeldPotato(APotato* potato);

	void OnUpdate_HeldPotato(APotato* old);

	UPROPERTY()
	UPotatoPickUpComponent* _potatoPickUpComponent = nullptr;

	UPROPERTY(Transient)
	APotato* _heldPotato = nullptr;

	UPROPERTY(Transient)
	USkeletalMeshComponent* _characterMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	FName _heldSocketName = FName("socket_hand_r");
};

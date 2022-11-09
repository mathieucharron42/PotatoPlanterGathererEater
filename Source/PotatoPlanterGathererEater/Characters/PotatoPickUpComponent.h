#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "PotatoPickUpComponent.generated.h"

class APotato;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTATOPLANTERGATHEREREATER_API UPotatoPickUpComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UPotatoPickUpComponent();

	bool IsHoldingPotato() const;

	void Authority_PickupPotato(APotato* potato);
	
	UFUNCTION(Server, Reliable)
	void Server_DropPotato();
	APotato* Authority_DropPotato();


protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type endPlayReason) override;

private:
	UFUNCTION()
	void OnOwnerOverlap(AActor* owningActor, AActor* otherActor);
	
	UFUNCTION()
	void OnOwnerHit(AActor* owningActor, AActor* otherActor, FVector normalImpulse, const FHitResult& hit);

	UFUNCTION()
	void OnRep_HeldPotato(APotato* old);

	void SetHeldPotato(APotato* potato);
	void OnUpdate_HeldPotato(APotato* old);

	UPROPERTY()
	UPotatoPickUpComponent* _potatoPickUpComponent = nullptr;

	UPROPERTY(Transient, Replicated, ReplicatedUsing = OnRep_HeldPotato)
	APotato* _heldPotato = nullptr;

	UPROPERTY(Transient)
	USkeletalMeshComponent* _characterMeshComponent = nullptr;
};

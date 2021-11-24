#pragma once


#include "Potato.h"
#include "PotatoBaseCharacter.h"

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"

#include "PotatoGathererCharacter.generated.h"

UCLASS(Abstract)
class POTATOGATHEREREATER_API APotatoGathererCharacter : public APotatoBaseCharacter
{
	GENERATED_BODY()
public:
	bool IsHoldingPotato() const;

private:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Authority_PickupPotato(APotato* potato);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_DropPotato();
	void Authority_DropPotato();

	UFUNCTION()
	void OnRep_HeldPotato(APotato* old);

	UPROPERTY(Transient, Replicated, ReplicatedUsing=OnRep_HeldPotato)
	APotato* _heldPotato = nullptr;

	UPROPERTY(Transient)
	USkeletalMeshComponent* _characterMeshComponent = nullptr;
};

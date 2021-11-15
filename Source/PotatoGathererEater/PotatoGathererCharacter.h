#pragma once


#include "Potato.h"
#include "PotatoBaseCharacter.h"

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"

#include "PotatoGathererCharacter.generated.h"

UCLASS()
class POTATOGATHEREREATER_API APotatoGathererCharacter : public APotatoBaseCharacter
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void PickupPotato(APotato* potato);
	void DropPotato();

	UPROPERTY(Transient)
	APotato* _heldPotato = nullptr;

	UPROPERTY(Transient)
	USkeletalMeshComponent* _characterMeshComponent = nullptr;
};

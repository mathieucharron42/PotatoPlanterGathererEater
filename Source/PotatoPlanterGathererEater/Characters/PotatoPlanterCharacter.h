#pragma once

#include "PotatoPlanterGathererEater/Characters/PotatoBaseCharacter.h"
#include "PotatoPlanterGathererEater/Crops/Potato.h"

#include "CoreMinimal.h"

#include "PotatoPlanterCharacter.generated.h"

UCLASS(Abstract)
class POTATOPLANTERGATHEREREATER_API APotatoPlanterCharacter : public APotatoBaseCharacter
{
	GENERATED_BODY()

public:
	APotatoPlanterCharacter();

	void Authority_PlantPotato();

	UFUNCTION(Server, Reliable)
	void Server_PlantPotato();
	
private:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	FVector _spawn;

	UPROPERTY(EditAnywhere)
	float _spawnVelocity;
};

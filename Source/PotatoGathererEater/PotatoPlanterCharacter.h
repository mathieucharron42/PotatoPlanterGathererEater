#pragma once

#include "CoreMinimal.h"

#include "PotatoBaseCharacter.h"
#include "Potato.h"

#include "PotatoPlanterCharacter.generated.h"

UCLASS(Abstract)
class POTATOGATHEREREATER_API APotatoPlanterCharacter : public APotatoBaseCharacter
{
	GENERATED_BODY()

public:
	void Authority_PlantPotato();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PlantPotato();
	
private:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void DisplayDebug(class UCanvas* Canvas, const class FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;
	UPROPERTY(EditAnywhere)
	FVector _spawn;

	UPROPERTY(EditAnywhere)
	float _spawnVelocity;
};

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
	void PlantPotato();
	
private:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float dt);

	UPROPERTY(EditAnywhere)
	FVector _spawn;

	UPROPERTY(EditAnywhere)
	float _spawnVelocity;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APotato>> _potatoTypes;
};

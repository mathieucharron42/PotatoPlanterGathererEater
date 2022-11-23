#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "PotatoPlantingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTATOPLANTERGATHEREREATER_API UPotatoPlantingComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UPotatoPlantingComponent();

	void Authority_PlantPotato();

protected:
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;

private:
	void OnSetupPlayerInput(UInputComponent* inputComponent);

	UPROPERTY(EditAnywhere)
	FName _spawnSocketName = FName("socket_spawn");

	UPROPERTY(EditAnywhere)
	float _spawnVelocity;
};

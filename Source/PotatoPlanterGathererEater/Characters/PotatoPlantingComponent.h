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

	UFUNCTION(Server, Reliable)
	void Server_PlantPotato();

private:
	UPROPERTY(EditAnywhere)
	FVector _spawn;

	UPROPERTY(EditAnywhere)
	float _spawnVelocity;
};

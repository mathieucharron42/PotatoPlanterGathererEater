// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FoodGroup.h"
#include "NutritionalInformations.h"

#include "Potato.generated.h"

class UDecayComponent;

UCLASS()
class POTATOGATHEREREATER_API APotato : public AActor
{
	GENERATED_BODY()
public:	
	APotato();

	float GetWeight() const { return _weight; }
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	UPROPERTY(EditAnywhere)
	float _weight;

	UPROPERTY(EditAnywhere)
	FNutritionalInformations _nutritionalInformations;

	UPROPERTY(EditAnywhere)
	UDecayComponent* _decayComponent;

	UPROPERTY(Transient)
	UObject* _foodGroup;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UFoodGroup> _foodGroupType;
};

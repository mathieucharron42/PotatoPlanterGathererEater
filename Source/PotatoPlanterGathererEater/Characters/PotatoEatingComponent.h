// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PotatoEatingComponent.generated.h"

class APotato;
class UPotatoPickUpComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POTATOPLANTERGATHEREREATER_API UPotatoEatingComponent : public USceneComponent
{
	GENERATED_BODY()

public:		
	UPotatoEatingComponent();

	DECLARE_MULTICAST_DELEGATE(FCaloriesEatenChanged);
	FCaloriesEatenChanged OnCaloriesEatenChanged;

	void Authority_EatHeldPotato();

	void Authority_EatPotato(APotato* potato);

	bool IsHungry() const;

	float GetCaloriesNeeded() const;

	float GetCaloriesEaten() const;

protected:
	virtual void InitializeComponent() override;

	virtual void UninitializeComponent() override;

private:
	void OnSetupPlayerInput(UInputComponent* inputComponent);

	void SetCaloriesEaten(float calories);

	UPROPERTY(EditAnywhere)
	float _caloriesNeeded;

	UPROPERTY(Transient)
	float _caloriesEaten;

	UPROPERTY(Transient)
	UPotatoPickUpComponent* _potatoPickUpComponent = nullptr;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FoodGroup.h"
#include "NutritionalInformations.h"

#include "Potato.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPotato, Log, All);

UCLASS(Abstract)
class POTATOPLANTERGATHEREREATER_API APotato : public AActor
{
	GENERATED_BODY()

public:	
	friend class UPotatoCheatManager;

	APotato();

	float GetWeight() const { return _weight; }

	const FNutritionalInformations& GetNutritionalInformations() const;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

private:
	void Cheat_Scale(float scale);

	UPROPERTY(EditAnywhere)
	float _weight;

	UPROPERTY(EditAnywhere)
	FNutritionalInformations _nutritionalInformations;

	UPROPERTY(Transient)
	UObject* _foodGroup;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UFoodGroup> _foodGroupType;
};

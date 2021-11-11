// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "DecayComponent.generated.h"

UCLASS()
class POTATOGATHEREREATER_API UDecayComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDecayComponent();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float _minimumTimeToLive = 0;

	UPROPERTY(EditAnywhere)
	float _maximumTimeToLive = 0;

	float _timeToLive = -1;
};

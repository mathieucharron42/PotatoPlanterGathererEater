// Fill out your copyright notice in the Description page of Project Settings.


#include "DecayComponent.h"

UDecayComponent::UDecayComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDecayComponent::BeginPlay()
{
	Super::BeginPlay();
	if (_maximumTimeToLive != 0)
	{
		_timeToLive = FMath::FRandRange(_maximumTimeToLive, _maximumTimeToLive);
	}
}

void UDecayComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UDecayComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (_timeToLive > 0)
	{
		_timeToLive -= DeltaTime;
		if (_timeToLive <= 0)
		{
			GetOwner()->Destroy();
		}
	}
}


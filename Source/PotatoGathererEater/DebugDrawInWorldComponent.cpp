// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugDrawInWorldComponent.h"
#include "DrawDebugHelpers.h"

UDebugDrawInWorldComponent::UDebugDrawInWorldComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDebugDrawInWorldComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UDebugDrawInWorldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UWorld* world = GetWorld();
	if (IsValid(world))
	{
		FVector position = GetComponentTransform().GetLocation();
		if (_pointEnabled)
		{
			DrawDebugPoint(world, position, _pointSize, _pointColor, false, _pointLifeTime, _pointDepthRenderingPriority);
		}
	}
}


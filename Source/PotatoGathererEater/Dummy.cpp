// Fill out your copyright notice in the Description page of Project Settings.


#include "Dummy.h"
#include "DebugDrawInWorldComponent.h"
#include <Components/SphereComponent.h>

#include "DrawDebugHelpers.h"

// Sets default values
ADummy::ADummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphape"));
	MeshComponent->SetupAttachment(RootComponent);
	
	DebugDrawInWorldComponent = CreateDefaultSubobject<UDebugDrawInWorldComponent>(TEXT("DebugDrawInWorld"));
	DebugDrawInWorldComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* world = GetWorld();
	if (IsValid(world))
	{
		FVector position = GetTransform().GetLocation();
		if (_pointEnabled)
		{ 
			DrawDebugPoint(world, position, _pointSize, _pointColor, false, _pointLifeTime, _pointDepthRenderingPriority);
		}
	}
}


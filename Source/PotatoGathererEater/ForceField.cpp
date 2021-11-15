// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceField.h"

// Sets default values
AForceField::AForceField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AForceField::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AForceField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


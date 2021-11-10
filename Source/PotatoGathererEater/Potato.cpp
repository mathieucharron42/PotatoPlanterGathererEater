// Fill out your copyright notice in the Description page of Project Settings.


#include "Potato.h"

// Sets default values
APotato::APotato()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APotato::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotato::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


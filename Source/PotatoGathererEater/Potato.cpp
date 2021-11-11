// Fill out your copyright notice in the Description page of Project Settings.


#include "Potato.h"
#include "PotatoManagerSubsystem.h"

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

	UPotatoManagerSubsystem* potatoManager = GetGameInstance()->GetSubsystem<UPotatoManagerSubsystem>();
	potatoManager->RegisterPotato(this);
}

// Called when the game starts or when spawned
void APotato::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);

	UPotatoManagerSubsystem* potatoManager = GetGameInstance()->GetSubsystem<UPotatoManagerSubsystem>();
	potatoManager->UnregisterPotato(this);
}


// Called every frame
void APotato::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


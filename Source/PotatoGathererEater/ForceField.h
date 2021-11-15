// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForceField.generated.h"

UCLASS()
class POTATOGATHEREREATER_API AForceField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AForceField();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

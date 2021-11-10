// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PotatoGathererEaterCharacter.h"
#include "Potato.h"

#include "PotatoPlanterCharacter.generated.h"

/**
 * 
 */
UCLASS()
class POTATOGATHEREREATER_API APotatoPlanterCharacter : public APotatoGathererEaterCharacter
{
	GENERATED_BODY()

	UFUNCTION()
	void Plant();
	
private:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	float _spawnDistance;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APotato> _potatoType;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "PotatoCheatManager.generated.h"

/**
 * 
 */
UCLASS()
class POTATOGATHEREREATER_API UPotatoCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
	UFUNCTION(Exec)
	void Potato_SpawnPotatoes(int32 amount);

	UFUNCTION(Exec)
	void Potato_ClearPotatoes();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "PotatoManagerSubsystem.generated.h"

class APotato;

UCLASS()
class POTATOGATHEREREATER_API UPotatoManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void RegisterPotato(APotato* potato);
	void UnregisterPotato(APotato* potato);

private:
	void RefreshPotatoDisplay();

	UPROPERTY()
	TArray<APotato*> _potatoes;
};

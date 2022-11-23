// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"

#include "PotatoGameState.generated.h"

UCLASS()
class POTATOPLANTERGATHEREREATER_API APotatoGameState : public AGameState
{
	GENERATED_BODY()

public:
	bool IsGameEnded();
	void SetGameEnded(bool completed);

private:
	UPROPERTY(Transient)
	bool _gameEnded = false;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PotatoBaseCharacter.h"
#include "PotatoGameRole.h"
#include "PotatoPlayerController.generated.h"

UCLASS()
class POTATOGATHEREREATER_API APotatoPlayerController : public APlayerController
{
	GENERATED_BODY()

	APotatoPlayerController();

	virtual void BeginPlay() override;

private:
	virtual void SetupInputComponent() override;

	void QuitGame();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ChangeRole();

	void Authority_ChangeRole();
};

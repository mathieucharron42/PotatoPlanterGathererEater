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

	virtual void BeginPlay() override;

private:
	virtual void SetupInputComponent() override;

	void ChangeRole();
};

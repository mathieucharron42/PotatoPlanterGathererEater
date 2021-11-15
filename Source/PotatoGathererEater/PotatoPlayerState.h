// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PotatoGameRole.h"
#include "PotatoPlayerState.generated.h"

UCLASS()
class POTATOGATHEREREATER_API APotatoPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	void SetCurrentRole(UPotatoGameRole* role);
	UPotatoGameRole* GetCurrentRole() const;

	UPROPERTY(Transient)
	UPotatoGameRole* _currentRole = nullptr;
};

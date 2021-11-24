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
	DECLARE_MULTICAST_DELEGATE(FRoleChanged);
	FRoleChanged& OnRoleChanged() { return _roleChangedEvent; }

	void SetCurrentRole(UPotatoGameRole* role);
	UPotatoGameRole* GetCurrentRole() const;

private:
	UFUNCTION()
	void OnRep_CurrentRole();

	UPROPERTY(Transient, Replicated, ReplicatedUsing=OnRep_CurrentRole)
	UPotatoGameRole* _currentRole = nullptr;

	FRoleChanged _roleChangedEvent;
};

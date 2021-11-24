// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoPlayerState.h"
#include "Net/UnrealNetwork.h"

void APotatoPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APotatoPlayerState, _currentRole);
}

void APotatoPlayerState::SetCurrentRole(UPotatoGameRole* role)
{
	_currentRole = role;
	OnRep_CurrentRole();
}

UPotatoGameRole* APotatoPlayerState::GetCurrentRole() const
{
	return _currentRole;
}

void APotatoPlayerState::OnRep_CurrentRole()
{
	OnRoleChanged().Broadcast();
}

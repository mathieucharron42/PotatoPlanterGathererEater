// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoPlayerState.h"

void APotatoPlayerState::SetCurrentRole(UPotatoGameRole* role)
{
	_currentRole = role;
}

UPotatoGameRole* APotatoPlayerState::GetCurrentRole() const
{
	return _currentRole;
}

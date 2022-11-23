#include "PotatoPlayerState.h"

#include "Net/UnrealNetwork.h"

void APotatoPlayerState::SetCurrentRole(FPotatoGameRole role)
{
	_currentRole = role;
}

FPotatoGameRole APotatoPlayerState::GetCurrentRole() const
{
	return _currentRole;
}

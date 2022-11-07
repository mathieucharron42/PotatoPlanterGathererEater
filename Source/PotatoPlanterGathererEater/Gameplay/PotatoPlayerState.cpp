#include "PotatoPlayerState.h"

#include "Net/UnrealNetwork.h"

void APotatoPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APotatoPlayerState, _currentRole);
}

void APotatoPlayerState::SetCurrentRole(FPotatoGameRole role)
{
	_currentRole = role;
	OnRep_CurrentRole();
}

FPotatoGameRole APotatoPlayerState::GetCurrentRole() const
{
	return _currentRole;
}

void APotatoPlayerState::OnRep_CurrentRole()
{
	OnRoleChanged().Broadcast();
}

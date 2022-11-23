#include "PotatoGameState.h"

#include "Net/UnrealNetwork.h"

bool APotatoGameState::IsGameEnded()
{
	return _gameEnded;
}

void APotatoGameState::SetGameEnded(bool completed)
{
	_gameEnded = completed;
}
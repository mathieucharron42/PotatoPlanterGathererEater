#include "PotatoGameState.h"

bool APotatoGameState::IsGameEnded()
{
	return _gameEnded;
}

void APotatoGameState::SetGameEnded(bool completed)
{
	_gameEnded = completed;
	GEngine->AddOnScreenDebugMessage(111, 60.f, FColor::Silver, FString::Printf(TEXT("COMPLETED!")), true, FVector2D(5.f, 5.0f));
}
#include "PotatoManagerSubsystem.h"

void UPotatoManagerSubsystem::RegisterPotato(APotato* potato)
{
	_potatoes.Add(potato);
	RefreshPotatoCount();
}

void UPotatoManagerSubsystem::UnregisterPotato(APotato* potato)
{
	_potatoes.Remove(potato);
	RefreshPotatoCount();
}

void UPotatoManagerSubsystem::RefreshPotatoCount()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%i potatoes"), _potatoes.Num()));
}

#include "PotatoManagerSubsystem.h"

void UPotatoManagerSubsystem::RegisterPotato(APotato* potato)
{
	_potatoes.Add(potato);
	RefreshPotatoDisplay();
}

void UPotatoManagerSubsystem::UnregisterPotato(APotato* potato)
{
	_potatoes.Remove(potato);
	RefreshPotatoDisplay();
}

void UPotatoManagerSubsystem::RefreshPotatoDisplay()
{
	static int32 key = 6666;
	GEngine->AddOnScreenDebugMessage(key, 5.f, FColor::Red, FString::Printf(TEXT("%i potatoes"), _potatoes.Num()));
}

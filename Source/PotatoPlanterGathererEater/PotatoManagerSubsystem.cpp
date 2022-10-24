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
	
}

#include "PotatoManagerSubsystem.h"

void UPotatoManagerSubsystem::RegisterPotato(APotato* potato)
{
	_potatoes.Add(potato);
}

void UPotatoManagerSubsystem::UnregisterPotato(APotato* potato)
{
	_potatoes.Remove(potato);
}

const TArray<APotato*> UPotatoManagerSubsystem::GetPotatoes() const
{
	return _potatoes;
}

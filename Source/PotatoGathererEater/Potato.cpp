#include "Potato.h"
#include "PotatoManagerSubsystem.h"

APotato::APotato()
{
	
}

void APotato::BeginPlay()
{
	Super::BeginPlay();

	_foodGroup = IsValid(_foodGroup) ? _foodGroupType->GetDefaultObject() : nullptr;

	UPotatoManagerSubsystem* potatoManager = GetGameInstance()->GetSubsystem<UPotatoManagerSubsystem>();
	potatoManager->RegisterPotato(this);
}

void APotato::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);

	UPotatoManagerSubsystem* potatoManager = GetGameInstance()->GetSubsystem<UPotatoManagerSubsystem>();
	potatoManager->UnregisterPotato(this);
}

const FNutritionalInformations& APotato::GetNutritionalInformations() const
{
	return _nutritionalInformations;
}


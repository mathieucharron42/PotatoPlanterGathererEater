#include "Potato.h"
#include "PotatoManagerSubsystem.h"

DEFINE_LOG_CATEGORY(LogPotato);

APotato::APotato()
{
	bReplicates = true;
	SetReplicateMovement(true);
}

void APotato::BeginPlay()
{
	Super::BeginPlay();

	_foodGroup = IsValid(_foodGroup) ? _foodGroupType->GetDefaultObject() : nullptr;

	UPotatoManagerSubsystem* potatoManager = GetGameInstance()->GetSubsystem<UPotatoManagerSubsystem>();
	potatoManager->RegisterPotato(this);

	UE_LOG(LogPotato, Log, TEXT("Spawned potato at %s"), *GetActorLocation().ToString())
}

void APotato::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);

	UPotatoManagerSubsystem* potatoManager = GetGameInstance()->GetSubsystem<UPotatoManagerSubsystem>();
	potatoManager->UnregisterPotato(this);

	UE_LOG(LogPotato, Log, TEXT("Unspawned potato at %s"), *GetActorLocation().ToString())
}

const FNutritionalInformations& APotato::GetNutritionalInformations() const
{
	return _nutritionalInformations;
}


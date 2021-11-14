#include "Potato.h"
#include "DecayComponent.h"
#include "PotatoManagerSubsystem.h"

APotato::APotato()
{
	PrimaryActorTick.bCanEverTick = true;

	_decayComponent = CreateDefaultSubobject<UDecayComponent>("DecayComponent");
	_decayComponent->bAutoRegister = true;
	//_foodGroup = StaticLoadObject(_foodGroupType, nullptr, TEXT("FoodGroup"));
}

void APotato::BeginPlay()
{
	Super::BeginPlay();

	_foodGroup = _foodGroupType->GetDefaultObject();

	UPotatoManagerSubsystem* potatoManager = GetGameInstance()->GetSubsystem<UPotatoManagerSubsystem>();
	potatoManager->RegisterPotato(this);
}

void APotato::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);

	UPotatoManagerSubsystem* potatoManager = GetGameInstance()->GetSubsystem<UPotatoManagerSubsystem>();
	potatoManager->UnregisterPotato(this);
}

void APotato::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


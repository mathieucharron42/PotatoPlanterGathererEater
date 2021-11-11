#include "DecayComponent.h"
#include "Potato.h"
#include "PotatoManagerSubsystem.h"

APotato::APotato()
{
	PrimaryActorTick.bCanEverTick = true;

	_decayComponent = CreateDefaultSubobject<UDecayComponent>("DecayComponent");
	_decayComponent->bAutoRegister = true;
}

void APotato::BeginPlay()
{
	Super::BeginPlay();

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


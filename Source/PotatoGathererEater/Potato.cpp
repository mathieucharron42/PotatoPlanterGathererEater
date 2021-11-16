#include "Potato.h"
#include "PotatoManagerSubsystem.h"

APotato::APotato()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APotato::BeginPlay()
{
	Super::BeginPlay();

	_foodGroup = _foodGroupType->GetDefaultObject();

	UPotatoManagerSubsystem* potatoManager = GetGameInstance()->GetSubsystem<UPotatoManagerSubsystem>();
	potatoManager->RegisterPotato(this);

	_staticMeshComponent = FindComponentByClass<UStaticMeshComponent>();

	SetIsPickedUp(false);
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

void APotato::SetIsPickedUp(bool isPickedUp)
{
	_isPickedUp = isPickedUp;
	if (_isPickedUp)
	{
		/*_staticMeshComponent->SetSimulatePhysics(false);
		_staticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);*/
	}
	else
	{
		//_staticMeshComponent->SetSimulatePhysics(true);
		/*_staticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);*/
	}
}

const FNutritionalInformations& APotato::GetNutritionalInformations() const
{
	return _nutritionalInformations;
}


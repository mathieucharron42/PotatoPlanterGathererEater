#include "PotatoGathererCharacter.h"

#include "PotatoPlanterGathererEater/Characters/PotatoPickUpComponent.h"

#include "Net/UnrealNetwork.h"

APotatoGathererCharacter::APotatoGathererCharacter()
{
	_potatoPickUpComponent = CreateDefaultSubobject<UPotatoPickUpComponent>(TEXT("PotatoPickUpComponent"));
	_potatoPickUpComponent->SetupAttachment(RootComponent);
}

bool APotatoGathererCharacter::IsHoldingPotato() const
{
	return _potatoPickUpComponent->IsHoldingPotato();
}

void APotatoGathererCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APotatoGathererCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, _potatoPickUpComponent, &UPotatoPickUpComponent::Server_DropPotato);
}

#include "PotatoPlanterCharacter.h"

#include "PotatoPlanterGathererEater/Gameplay/PotatoGameMode.h"
#include "PotatoPlanterGathererEater/Characters/PotatoPlantingComponent.h"
#include "PotatoPlanterGathererEater/Characters/PotatoPickUpComponent.h"

#include "Components/InputComponent.h"


APotatoPlanterCharacter::APotatoPlanterCharacter()
{
	_potatoPlantingComponent = CreateDefaultSubobject<UPotatoPlantingComponent>(TEXT("UPotatoPlantComponent"));
	_potatoPlantingComponent->SetupAttachment(RootComponent);

	_potatoPickUpComponent = CreateDefaultSubobject<UPotatoPickUpComponent>(TEXT("PotatoPickUpComponent"));
	_potatoPickUpComponent->SetupAttachment(RootComponent);
}

void APotatoPlanterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, _potatoPlantingComponent, &UPotatoPlantingComponent::Server_PlantPotato);
	PlayerInputComponent->BindAction("Release", IE_Pressed, _potatoPickUpComponent, &UPotatoPickUpComponent::Server_DropPotato);
}
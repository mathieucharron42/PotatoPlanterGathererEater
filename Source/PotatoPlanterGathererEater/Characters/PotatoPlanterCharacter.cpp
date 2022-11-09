#include "PotatoPlanterCharacter.h"

#include "PotatoPlanterGathererEater/Gameplay/PotatoGameMode.h"
#include "PotatoPlanterGathererEater/Characters/PotatoPlantingComponent.h"

#include "Components/InputComponent.h"


APotatoPlanterCharacter::APotatoPlanterCharacter()
{
	_potatoPlantingComponent = CreateDefaultSubobject<UPotatoPlantingComponent>(TEXT("UPotatoPlantComponent"));
	_potatoPlantingComponent->SetupAttachment(RootComponent);
}

void APotatoPlanterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, _potatoPlantingComponent, &UPotatoPlantingComponent::Server_PlantPotato);
}
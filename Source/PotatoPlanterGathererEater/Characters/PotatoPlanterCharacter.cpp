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
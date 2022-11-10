#include "PotatoGathererCharacter.h"

#include "PotatoPlanterGathererEater/Characters/PotatoPickUpComponent.h"

APotatoGathererCharacter::APotatoGathererCharacter()
{
	_potatoPickUpComponent = CreateDefaultSubobject<UPotatoPickUpComponent>(TEXT("PotatoPickUpComponent"));
	_potatoPickUpComponent->SetupAttachment(RootComponent);
}
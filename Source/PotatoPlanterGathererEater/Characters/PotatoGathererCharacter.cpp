#include "PotatoGathererCharacter.h"

#include "PotatoPlanterGathererEater/Characters/PotatoPickUpComponent.h"

#include "Net/UnrealNetwork.h"

APotatoGathererCharacter::APotatoGathererCharacter()
{
	_potatoPickUpComponent = CreateDefaultSubobject<UPotatoPickUpComponent>(TEXT("PotatoPickUpComponent"));
	_potatoPickUpComponent->SetupAttachment(RootComponent);
}
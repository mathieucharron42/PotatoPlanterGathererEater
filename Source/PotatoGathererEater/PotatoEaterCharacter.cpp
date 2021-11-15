#include "PotatoEaterCharacter.h"

void APotatoEaterCharacter::BeginPlay()
{
	Super::BeginPlay();
	_springArmComponent = FindComponentByClass<USpringArmComponent>();
	_initialSpringArmLenght = _springArmComponent->TargetArmLength;
}

void APotatoEaterCharacter::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	if (otherActor->IsA<APotato>())
	{
		APotato* potato = Cast<APotato>(otherActor);
		EatPotato(potato);
	}
}

void APotatoEaterCharacter::UpdateVisual()
{
	// Double the size for every 500g
	float scaleRatio = 1 + (_amountEaten / 500.f);
	SetActorScale3D(FVector(scaleRatio, scaleRatio, scaleRatio));
	_springArmComponent->TargetArmLength = _initialSpringArmLenght * scaleRatio;
}

void APotatoEaterCharacter::EatPotato(APotato* potato)
{
	_amountEaten += potato->GetWeight();
	potato->Destroy();
	UpdateVisual();
}

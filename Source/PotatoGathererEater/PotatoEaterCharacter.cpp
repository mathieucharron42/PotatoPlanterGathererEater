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
	const float scale = 1.f + _caloriesEaten * _caloryScale;
	SetScale(scale);
}

void APotatoEaterCharacter::EatPotato(APotato* potato)
{
	const FNutritionalInformations& nutritionalInformations = potato->GetNutritionalInformations();
	_caloriesEaten += nutritionalInformations.GetCalories(potato->GetWeight());
	potato->Destroy();
	UpdateVisual();
}

bool APotatoEaterCharacter::IsHungry() const
{
	return _caloriesEaten < _caloriesNeeded;
}

void APotatoEaterCharacter::Tick(float dt)
{
	Super::Tick(dt);
	if (IsPlayerControlled())
	{
		GEngine->AddOnScreenDebugMessage(555, 0.f, FColor::Red, TEXT("Currently possessing a potato eater"));
		GEngine->AddOnScreenDebugMessage(556, 0.f, FColor::Red, TEXT("Move over potatoes to eat them"));
		GEngine->AddOnScreenDebugMessage(557, 0.f, FColor::Red, FString::Printf(TEXT("%f / %f calories"), _caloriesEaten, _caloriesNeeded));
	}
}

void APotatoEaterCharacter::SetScale_Implementation(float scale)
{
	SetActorScale3D(FVector(scale, scale, scale));
	_springArmComponent->TargetArmLength = _initialSpringArmLenght * scale;
}

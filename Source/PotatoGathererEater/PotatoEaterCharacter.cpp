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

void APotatoEaterCharacter::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (Other->IsA<APotato>())
	{
		APotato* potato = Cast<APotato>(Other);
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

float APotatoEaterCharacter::GetCaloriesNeeded() const 
{ 
	return _caloriesNeeded; 
}

float APotatoEaterCharacter::GetCaloriesEaten() const 
{ 
	return _caloriesEaten; 
}

void APotatoEaterCharacter::SetScale_Implementation(float scale)
{
	SetActorScale3D(FVector(scale, scale, scale));
	_springArmComponent->TargetArmLength = _initialSpringArmLenght * scale;
}

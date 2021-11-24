#include "PotatoEaterCharacter.h"
#include "Net/UnrealNetwork.h"

void APotatoEaterCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APotatoEaterCharacter, _caloriesEaten);
}

void APotatoEaterCharacter::BeginPlay()
{
	Super::BeginPlay();
	_springArmComponent = FindComponentByClass<USpringArmComponent>();
	_initialSpringArmLenght = _springArmComponent->TargetArmLength;
}

void APotatoEaterCharacter::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	if (HasAuthority())
	{
		if (otherActor->IsA<APotato>())
		{
			APotato* potato = Cast<APotato>(otherActor);
			Authority_EatPotato(potato);
		}
	}
}

void APotatoEaterCharacter::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	if (HasAuthority())
	{
		if (Other->IsA<APotato>())
		{
			APotato* potato = Cast<APotato>(Other);
			Authority_EatPotato(potato);
		}
	}
}

void APotatoEaterCharacter::Authority_UpdateVisual()
{
	if (ensure(HasAuthority()))
	{
		const float scale = 1.f + _caloriesEaten * _caloryScale;
		Client_Multicast_SetScale(scale);
	}
}

void APotatoEaterCharacter::Authority_EatPotato(APotato* potato)
{
	if (ensure(HasAuthority()))
	{
		const FNutritionalInformations& nutritionalInformations = potato->GetNutritionalInformations();
		_caloriesEaten += nutritionalInformations.GetCalories(potato->GetWeight());
		potato->Destroy();
		Authority_UpdateVisual();
	}
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

void APotatoEaterCharacter::Client_Multicast_SetScale_Implementation(float scale)
{
	Local_SetScale(scale);
}

void APotatoEaterCharacter::Local_SetScale_Implementation(float scale)
{
	SetActorScale3D(FVector(scale, scale, scale));
	_springArmComponent->TargetArmLength = _initialSpringArmLenght * scale;
}

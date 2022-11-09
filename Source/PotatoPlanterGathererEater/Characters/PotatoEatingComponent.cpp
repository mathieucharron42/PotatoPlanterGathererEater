#include "PotatoEatingComponent.h"

#include "PotatoPlanterGathererEater/Characters/PotatoPickUpComponent.h"
#include "PotatoPlanterGathererEater/Crops/Potato.h"

#include "Net/UnrealNetwork.h"

UPotatoEatingComponent::UPotatoEatingComponent()
{
}

void UPotatoEatingComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPotatoEatingComponent, _caloriesEaten);
}

void UPotatoEatingComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		_potatoPickUpComponent = owner->FindComponentByClass<UPotatoPickUpComponent>();
	}
}

void UPotatoEatingComponent::EndPlay(EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		
	}
}

void UPotatoEatingComponent::SetCaloriesEaten(float calories)
{
	float old = _caloriesEaten;
	_caloriesEaten = calories;
	if (old != _caloriesEaten)
	{
		OnCaloriesEatenChanged.Broadcast();
	}
}

void UPotatoEatingComponent::Server_EatPotato_Implementation(APotato* potato)
{
	Authority_EatPotato(potato);
}

void UPotatoEatingComponent::Authority_EatPotato(APotato* potato)
{
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		if (ensure(owner->HasAuthority()))
		{
			const FNutritionalInformations& nutritionalInformations = potato->GetNutritionalInformations();
			float newCalories = nutritionalInformations.GetCalories(potato->GetWeight());
			SetCaloriesEaten(GetCaloriesEaten() + newCalories);
			potato->Destroy();
		}
	}
}

bool UPotatoEatingComponent::IsHungry() const
{
	return _caloriesEaten < _caloriesNeeded;
}

float UPotatoEatingComponent::GetCaloriesNeeded() const
{
	return _caloriesNeeded;
}

float UPotatoEatingComponent::GetCaloriesEaten() const
{
	return _caloriesEaten;
}

void UPotatoEatingComponent::Server_EatHeldPotato_Implementation()
{
	if (_potatoPickUpComponent->IsHoldingPotato())
	{
		APotato* potato = _potatoPickUpComponent->Authority_RemovePotato();
		Authority_EatPotato(potato);
	}
}

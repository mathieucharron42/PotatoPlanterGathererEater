#include "PotatoEatingComponent.h"

#include "PotatoPlanterGathererEater/Characters/PotatoBaseCharacter.h"
#include "PotatoPlanterGathererEater/Characters/PotatoPickUpComponent.h"
#include "PotatoPlanterGathererEater/Crops/Potato.h"

#include "Components/InputComponent.h"
#include "Net/UnrealNetwork.h"

UPotatoEatingComponent::UPotatoEatingComponent()
{
	bWantsInitializeComponent = true;
}

void UPotatoEatingComponent::InitializeComponent()
{
	Super::InitializeComponent();
	APotatoBaseCharacter* owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(owner)))
	{
		_potatoPickUpComponent = owner->FindComponentByClass<UPotatoPickUpComponent>();
		owner->OnSetupPlayerInput.AddUObject(this, &UPotatoEatingComponent::OnSetupPlayerInput);
	}
}

void UPotatoEatingComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
	APotatoBaseCharacter* owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (IsValid(owner))
	{
		owner->OnSetupPlayerInput.RemoveAll(this);
	}
}

void UPotatoEatingComponent::OnSetupPlayerInput(UInputComponent* inputComponent)
{
	if (ensure(IsValid(inputComponent)))
	{
		inputComponent->BindAction("Fire", IE_Pressed, this, &UPotatoEatingComponent::Authority_EatHeldPotato);
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

void UPotatoEatingComponent::Authority_EatHeldPotato()
{
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		if (ensure(owner->HasAuthority()))
		{
			if (_potatoPickUpComponent->IsHoldingPotato())
			{
				APotato* potato = _potatoPickUpComponent->Authority_ReleasePotato();
				Authority_EatPotato(potato);
			}
		}
	}
}
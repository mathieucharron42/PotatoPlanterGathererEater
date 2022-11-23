#include "PotatoEaterCharacter.h"

#include "PotatoPlanterGathererEater/Characters/PotatoEatingComponent.h"
#include "PotatoPlanterGathererEater/Characters/PotatoPickUpComponent.h"

#include "GameFramework/SpringArmComponent.h"

#include "Net/UnrealNetwork.h"

APotatoEaterCharacter::APotatoEaterCharacter()
{
	_potatoEatingComponent = CreateDefaultSubobject<UPotatoEatingComponent>(TEXT("PotatoEatingComponent"));
	_potatoEatingComponent->SetupAttachment(RootComponent);

	_potatoPickUpComponent = CreateDefaultSubobject<UPotatoPickUpComponent>(TEXT("PotatoPickUpComponent"));
	_potatoPickUpComponent->SetupAttachment(RootComponent);
}

void APotatoEaterCharacter::BeginPlay()
{
	Super::BeginPlay();
	_springArmComponent = FindComponentByClass<USpringArmComponent>();
	_initialSpringArmLenght = _springArmComponent->TargetArmLength;

	_potatoEatingComponent->OnCaloriesEatenChanged.AddUObject(this, &APotatoEaterCharacter::OnCaloriesEatenChanged);
}

void APotatoEaterCharacter::EndPlay(EEndPlayReason::Type reason)
{
	_potatoEatingComponent->OnCaloriesEatenChanged.RemoveAll(this);
}

void APotatoEaterCharacter::OnCaloriesEatenChanged()
{
	if (HasAuthority())
	{
		const float scale = 1.f + _potatoEatingComponent->GetCaloriesEaten() * _caloryScale;
		Authority_SetScale(scale);
	}
}

void APotatoEaterCharacter::Authority_SetScale(float scale)
{
	if (HasAuthority())
	{
		float oldScale = _currentScale;
		_currentScale = scale;
		OnUpdate_CurrentScale(oldScale);
	}
}

void APotatoEaterCharacter::OnUpdate_CurrentScale(float oldScale)
{
	SetActorScale3D(FVector(_currentScale, _currentScale, _currentScale));
	_springArmComponent->TargetArmLength = _initialSpringArmLenght * _currentScale;
}
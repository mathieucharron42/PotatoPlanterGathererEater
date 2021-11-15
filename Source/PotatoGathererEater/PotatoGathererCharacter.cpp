#include "PotatoGathererCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Potato.h"

void APotatoGathererCharacter::BeginPlay()
{
	Super::BeginPlay();
	UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
	_characterMeshComponent = this->FindComponentByClass<USkeletalMeshComponent>();
}

void APotatoGathererCharacter::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	if (otherActor->IsA<APotato>())
	{
		APotato* potato = Cast<APotato>(otherActor);
		PickupPotato(potato);
	}
}

void APotatoGathererCharacter::PickupPotato(APotato* potato)
{
	if (!IsValid(_heldPotato))
	{
		if (!potato->IsAttachedTo(this))
		{
			_heldPotato = potato;
			_heldPotato->SetIsPickedUp(true);
			_heldPotato->AttachToComponent(_characterMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("socket_hand_r"));
			//_heldPotato->SetActorTransform(FTransform());
		}
	}
}

void APotatoGathererCharacter::DropPotato()
{
	if (IsValid(_heldPotato))
	{
		_heldPotato->DetachRootComponentFromParent(true);
		_heldPotato->SetIsPickedUp(false);
		_heldPotato = nullptr;
	}
}

void APotatoGathererCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APotatoGathererCharacter::DropPotato);
}
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
	if (!IsHoldingPotato())
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
	if (IsHoldingPotato())
	{
		_heldPotato->DetachRootComponentFromParent(true);
		_heldPotato->SetIsPickedUp(false);
		_heldPotato = nullptr;
	}
}

bool APotatoGathererCharacter::IsHoldingPotato() const
{
	return IsValid(_heldPotato);
}

void APotatoGathererCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APotatoGathererCharacter::DropPotato);
}

void APotatoGathererCharacter::Tick(float dt)
{
	Super::Tick(dt);
	if (IsPlayerControlled())
	{
		const FColor color = FColor(141, 154, 203);
		GEngine->AddOnScreenDebugMessage(333, 0.001f, color, TEXT("Currently possessing a potato gatherer"));
		GEngine->AddOnScreenDebugMessage(334, 0.001f, color, TEXT("Move over a potato to pick one up and right click to drop it"));
		GEngine->AddOnScreenDebugMessage(335, 0.001f, color, FString::Printf(TEXT("Is holding potato: %s"), IsHoldingPotato() ? TEXT("true") : TEXT("false")));
	}
}
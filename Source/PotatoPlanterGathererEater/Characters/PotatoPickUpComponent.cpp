#include "PotatoPickUpComponent.h"

#include "PotatoPlanterGathererEater/Crops/Potato.h"
#include "PotatoPlanterGathererEater/Characters/PotatoBaseCharacter.h"

#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"

UPotatoPickUpComponent::UPotatoPickUpComponent()
{
	bWantsInitializeComponent = true;
}

void UPotatoPickUpComponent::InitializeComponent()
{
	Super::InitializeComponent();
	APotatoBaseCharacter* owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(owner)))
	{
		_characterMeshComponent = owner->FindComponentByClass<USkeletalMeshComponent>();
		owner->OnActorBeginOverlap.AddDynamic(this, &UPotatoPickUpComponent::OnOwnerOverlap);
		owner->OnActorHit.AddDynamic(this, &UPotatoPickUpComponent::OnOwnerHit);
		owner->OnSetupPlayerInput.AddUObject(this, &UPotatoPickUpComponent::OnSetupPlayerInput);
	}
}

void UPotatoPickUpComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
	APotatoBaseCharacter* owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (IsValid(owner))
	{
		owner->OnActorBeginOverlap.RemoveDynamic(this, &UPotatoPickUpComponent::OnOwnerOverlap);
		owner->OnActorHit.RemoveDynamic(this, &UPotatoPickUpComponent::OnOwnerHit);
		owner->OnSetupPlayerInput.RemoveAll(this);
	}
}

void UPotatoPickUpComponent::OnOwnerOverlap(AActor* owningActor, AActor* otherActor)
{
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		if (owner->HasAuthority())
		{
			if (otherActor->IsA<APotato>())
			{
				APotato* potato = Cast<APotato>(otherActor);
				Authority_PickupPotato(potato);
			}
		}
	}
}

void UPotatoPickUpComponent::OnOwnerHit(AActor* owningActor, AActor* otherActor, FVector normalImpulse, const FHitResult& hit)
{
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		if (owner->HasAuthority())
		{
			if (otherActor->IsA<APotato>())
			{
				APotato* potato = Cast<APotato>(otherActor);
				Authority_PickupPotato(potato);
			}
		}
	}
}

void UPotatoPickUpComponent::OnSetupPlayerInput(UInputComponent* inputComponent)
{
	inputComponent->BindAction("Release", IE_Pressed, this, &UPotatoPickUpComponent::Authority_DropPotato);
}

void UPotatoPickUpComponent::Authority_PickupPotato(APotato* potato)
{
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		if (ensure(owner->HasAuthority()))
		{
			if (!IsHoldingPotato())
			{
				SetHeldPotato(potato);
			}
		}
	}
}

void UPotatoPickUpComponent::Authority_DropPotato()
{
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		if (ensure(owner->HasAuthority()))
		{
			if (IsHoldingPotato())
			{
				SetHeldPotato(nullptr);
			}
		}
	}
}

APotato* UPotatoPickUpComponent::Authority_ReleasePotato()
{
	APotato* potato = _heldPotato;

	Authority_DropPotato();

	return potato;
}

bool UPotatoPickUpComponent::IsHoldingPotato() const
{
	return IsValid(_heldPotato);
}

void UPotatoPickUpComponent::OnRep_HeldPotato(APotato* old)
{
	OnUpdate_HeldPotato(old);
}

void UPotatoPickUpComponent::SetHeldPotato(APotato* potato)
{
	APotato* previous = _heldPotato;
	_heldPotato = potato;
	OnUpdate_HeldPotato(previous);
}

void UPotatoPickUpComponent::OnUpdate_HeldPotato(APotato* old)
{
	if (IsValid(_heldPotato))
	{
		UPrimitiveComponent* targetComponent = Cast<UPrimitiveComponent>(_heldPotato->GetRootComponent());

		targetComponent->SetSimulatePhysics(false);
		targetComponent->SetEnableGravity(false);
		targetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FAttachmentTransformRules attachementRules = FAttachmentTransformRules::SnapToTargetIncludingScale;
		attachementRules.bWeldSimulatedBodies = true;
		attachementRules.ScaleRule = EAttachmentRule::KeepRelative;
		targetComponent->AttachToComponent(_characterMeshComponent, attachementRules, _heldSocketName);
	}
	else if (IsValid(old))
	{
		UPrimitiveComponent* targetComponent = Cast<UPrimitiveComponent>(old->GetRootComponent());

		FDetachmentTransformRules detachementRules = FDetachmentTransformRules::KeepWorldTransform;
		detachementRules.ScaleRule = EDetachmentRule::KeepRelative;
		old->DetachFromActor(detachementRules);

		targetComponent->SetSimulatePhysics(true);
		targetComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		targetComponent->SetEnableGravity(true);
	}
}
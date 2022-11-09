#include "PotatoPickUpComponent.h"

#include "PotatoPlanterGathererEater/Crops/Potato.h"

#include "Net/UnrealNetwork.h"

UPotatoPickUpComponent::UPotatoPickUpComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPotatoPickUpComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPotatoPickUpComponent, _heldPotato);
}

void UPotatoPickUpComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		_characterMeshComponent = owner->FindComponentByClass<USkeletalMeshComponent>();
		owner->OnActorBeginOverlap.AddDynamic(this, &UPotatoPickUpComponent::OnOwnerOverlap);
		owner->OnActorHit.AddDynamic(this, &UPotatoPickUpComponent::OnOwnerHit);
	}
}

void UPotatoPickUpComponent::EndPlay(EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		owner->OnActorBeginOverlap.RemoveDynamic(this, &UPotatoPickUpComponent::OnOwnerOverlap);
		owner->OnActorHit.RemoveDynamic(this, &UPotatoPickUpComponent::OnOwnerHit);
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

void UPotatoPickUpComponent::Server_DropPotato_Implementation()
{
	Authority_DropPotato();
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
		targetComponent->AttachToComponent(_characterMeshComponent, attachementRules, FName("socket_hand_r"));
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
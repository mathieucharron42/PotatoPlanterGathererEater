#include "PotatoGathererCharacter.h"
#include "Net/UnrealNetwork.h"

void APotatoGathererCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APotatoGathererCharacter, _heldPotato);
}

void APotatoGathererCharacter::BeginPlay()
{
	Super::BeginPlay();
	UCapsuleComponent* capsuleComponent = GetCapsuleComponent();
	_characterMeshComponent = this->FindComponentByClass<USkeletalMeshComponent>();
}

void APotatoGathererCharacter::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	if (HasAuthority())
	{
		if (otherActor->IsA<APotato>())
		{
			APotato* potato = Cast<APotato>(otherActor);
			Authority_PickupPotato(potato);
		}
	}
}

void APotatoGathererCharacter::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (HasAuthority())
	{
		if (Other->IsA<APotato>())
		{
			APotato* potato = Cast<APotato>(Other);
			Authority_PickupPotato(potato);
		}
	}
}

void APotatoGathererCharacter::Authority_PickupPotato(APotato* potato)
{
	if (ensure(HasAuthority()))
	{
		if (!IsHoldingPotato())
		{
			APotato* previous = _heldPotato;
			_heldPotato = potato;
			OnRep_HeldPotato(previous);
		}
	}
}

void APotatoGathererCharacter::Server_DropPotato_Implementation()
{
	Authority_DropPotato();
}

bool APotatoGathererCharacter::Server_DropPotato_Validate()
{
	return true;
}

void APotatoGathererCharacter::Authority_DropPotato()
{
	if (ensure(HasAuthority()))
	{
		if (IsHoldingPotato())
		{
			APotato* previous = _heldPotato;
			_heldPotato = nullptr;
			OnRep_HeldPotato(previous);
		}
	}
}

bool APotatoGathererCharacter::IsHoldingPotato() const
{
	return IsValid(_heldPotato);
}

void APotatoGathererCharacter::OnRep_HeldPotato(APotato* old)
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

void APotatoGathererCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APotatoGathererCharacter::Server_DropPotato);
}

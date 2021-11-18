#include "PotatoGathererCharacter.h"

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

void APotatoGathererCharacter::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (Other->IsA<APotato>())
	{
		APotato* potato = Cast<APotato>(Other);
		PickupPotato(potato);
	}
}

void APotatoGathererCharacter::PickupPotato(APotato* potato)
{
	if (!IsHoldingPotato())
	{
		_heldPotato = potato;

		UPrimitiveComponent* targetComponent = Cast<UPrimitiveComponent>(_heldPotato->GetRootComponent());

		targetComponent->SetSimulatePhysics(false);
		targetComponent->SetEnableGravity(false);
		targetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		FAttachmentTransformRules attachementRules = FAttachmentTransformRules::SnapToTargetIncludingScale;
		attachementRules.bWeldSimulatedBodies = true;
		attachementRules.ScaleRule = EAttachmentRule::KeepRelative;
		targetComponent->AttachToComponent(_characterMeshComponent, attachementRules, FName("socket_hand_r"));
	}
}

void APotatoGathererCharacter::DropPotato()
{
	if (IsHoldingPotato())
	{
		UPrimitiveComponent* targetComponent = Cast<UPrimitiveComponent>(_heldPotato->GetRootComponent());

		FDetachmentTransformRules detachementRules = FDetachmentTransformRules::KeepWorldTransform;
		detachementRules.ScaleRule = EDetachmentRule::KeepRelative;
		_heldPotato->DetachFromActor(detachementRules);

		targetComponent->SetSimulatePhysics(true);
		targetComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		targetComponent->SetEnableGravity(true);

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
		GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("Currently possessing a potato gatherer. Press tab to change character."), false);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, color, TEXT("Move over a potato to pick one up and right click to drop it"), false);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, color, FString::Printf(TEXT("Is holding potato: %s"), IsHoldingPotato() ? TEXT("true") : TEXT("false")), false);
	}
}
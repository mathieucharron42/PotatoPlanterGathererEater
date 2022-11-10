#include "PotatoPlantingComponent.h"

#include "PotatoPlanterGathererEater/Gameplay/PotatoGameMode.h"

#include "Kismet/KismetMathLibrary.h"

UPotatoPlantingComponent::UPotatoPlantingComponent()
{
	bWantsInitializeComponent = true;
}

void UPotatoPlantingComponent::Authority_PlantPotato()
{
	ACharacter* owner = Cast<ACharacter>(GetOwner());
	if (ensure(IsValid(owner)))
	{
		if (ensure(owner->HasAuthority()))
		{
			UWorld* world = GetWorld();
			if (ensure(IsValid(world)))
			{
				USkeletalMeshComponent* meshComponent = owner->GetMesh();
				if (ensure(IsValid(meshComponent)) && ensure(meshComponent->DoesSocketExist(_spawnSocketName)))
				{
					// Locate socket for location
					FTransform newPotatoTransform = meshComponent->GetSocketTransform(_spawnSocketName);

					// Set random rotation on potato
					newPotatoTransform.SetRotation(UKismetMathLibrary::RandomRotator(true).Quaternion());

					// Set random velocity in 45 degree half-cone 
					FVector newPotatoVelocity = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(owner->GetTransform().GetUnitAxis(EAxis::X), 45.f) * _spawnVelocity;
					newPotatoVelocity.Z = FMath::Abs(newPotatoVelocity.Z);

					DrawDebugLine(GetWorld(), newPotatoTransform.GetLocation(), newPotatoTransform.GetLocation() + newPotatoVelocity, FColor::Red, false, 5);

					APotatoGameMode* gameMode = world->GetAuthGameMode<APotatoGameMode>();
					if (ensure(IsValid(gameMode)))
					{
						gameMode->SpawnPotato(newPotatoTransform, newPotatoVelocity);
					}
				}
			}
		}
	}
}

void UPotatoPlantingComponent::Server_PlantPotato_Implementation()
{
	Authority_PlantPotato();
}

void UPotatoPlantingComponent::InitializeComponent()
{
	Super::InitializeComponent();
	APotatoBaseCharacter* owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(owner)))
	{
		owner->OnSetupPlayerInput.AddUObject(this, &UPotatoPlantingComponent::OnSetupPlayerInput);
	}
}

void UPotatoPlantingComponent::UninitializeComponent()
{
	Super::UninitializeComponent();
	APotatoBaseCharacter* owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (IsValid(owner))
	{
		owner->OnSetupPlayerInput.RemoveAll(this);
	}
}

void UPotatoPlantingComponent::OnSetupPlayerInput(UInputComponent* inputComponent)
{
	inputComponent->BindAction("Fire", IE_Pressed, this, &UPotatoPlantingComponent::Server_PlantPotato);
}


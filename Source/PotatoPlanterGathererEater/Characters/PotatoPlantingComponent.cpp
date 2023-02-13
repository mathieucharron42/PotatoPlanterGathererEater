#include "PotatoPlantingComponent.h"

#include "PotatoPlanterGathererEater/Crops/Potato.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoGameMode.h"
#include "PotatoPlanterGathererEater/Utils/PotatoUtilities.h"

#include "Kismet/KismetMathLibrary.h"

UPotatoPlantingComponent::UPotatoPlantingComponent()
{
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
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

					APotatoGameMode* gameMode = world->GetAuthGameMode<APotatoGameMode>();
					if (ensure(IsValid(gameMode)))
					{
						APotato* newPotato = gameMode->SpawnPotato(newPotatoTransform, newPotatoVelocity);
						UE_LOG(LogPotato, Log, TEXT("Spawned potato %s by %s at %s"), *newPotato->GetName(), *owner->GetName(), *owner->GetTransform().ToString());
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


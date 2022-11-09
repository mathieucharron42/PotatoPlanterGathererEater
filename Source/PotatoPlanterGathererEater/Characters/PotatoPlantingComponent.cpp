#include "PotatoPlantingComponent.h"

#include "PotatoPlanterGathererEater/Gameplay/PotatoGameMode.h"

#include "Kismet/KismetMathLibrary.h"

UPotatoPlantingComponent::UPotatoPlantingComponent()
{

}

void UPotatoPlantingComponent::Authority_PlantPotato()
{
	AActor* owner = GetOwner();
	if (ensure(IsValid(owner)))
	{
		if (ensure(owner->HasAuthority()))
		{
			UWorld* world = GetWorld();
			if (IsValid(world))
			{
				APotatoGameMode* gameMode = world->GetAuthGameMode<APotatoGameMode>();
				if (ensure(IsValid(gameMode)))
				{
					FTransform characterTransform = owner->GetTransform();

					FTransform potatoTransform = characterTransform;
					{
						FVector relativeLocation = characterTransform.GetRotation().RotateVector(_spawn);
						potatoTransform.AddToTranslation(relativeLocation);
						FRotator relativeRotation = UKismetMathLibrary::RandomRotator(true);
						potatoTransform.SetRotation(relativeRotation.Quaternion());
					}

					FVector randomVelocity = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(characterTransform.GetUnitAxis(EAxis::X), 45.f) * _spawnVelocity;
					randomVelocity.Z = FMath::Abs(randomVelocity.Z);
					//DrawDebugLine(GetWorld(), potatoTransform.GetLocation(), potatoTransform.GetLocation() + randomVelocity, FColor::Red, false, 5);

					gameMode->SpawnPotato(potatoTransform, randomVelocity);
				}
			}
		}
	}
}

void UPotatoPlantingComponent::Server_PlantPotato_Implementation()
{
	Authority_PlantPotato();
}

void UPotatoPlantingComponent::OnRegister()
{
	Super::OnRegister();
	APotatoBaseCharacter* owner = Cast<APotatoBaseCharacter>(GetOwner());
	if (ensure(IsValid(owner)))
	{
		owner->OnSetupPlayerInput.AddUObject(this, &UPotatoPlantingComponent::OnSetupPlayerInput);
	}
}

void UPotatoPlantingComponent::OnUnregister()
{
	Super::OnUnregister();
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


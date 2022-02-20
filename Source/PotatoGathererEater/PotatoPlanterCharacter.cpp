// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoPlanterCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "PotatoGameMode.h"

void APotatoPlanterCharacter::Authority_PlantPotato()
{
	if (ensure(HasAuthority()))
	{
		UWorld* world = GetWorld();
		if (IsValid(world))
		{
			APotatoGameMode* gameMode = world->GetAuthGameMode<APotatoGameMode>();
			if (ensure(IsValid(gameMode)))
			{
				FTransform planterTransform = GetTransform();

				FTransform potatoTransform = planterTransform;
				{
					FVector relativeLocation = planterTransform.GetRotation().RotateVector(_spawn);
					potatoTransform.AddToTranslation(relativeLocation);
					FRotator relativeRotation = UKismetMathLibrary::RandomRotator(true);
					potatoTransform.SetRotation(relativeRotation.Quaternion());
				}

				FVector randomVelocity = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(planterTransform.GetUnitAxis(EAxis::X), 45.f) * _spawnVelocity;
				randomVelocity.Z = FMath::Abs(randomVelocity.Z);
				//DrawDebugLine(GetWorld(), potatoTransform.GetLocation(), potatoTransform.GetLocation() + randomVelocity, FColor::Red, false, 5);

				gameMode->SpawnPotato(potatoTransform, randomVelocity);
			}
		}
	}
}

void APotatoPlanterCharacter::Server_PlantPotato_Implementation()
{
	Authority_PlantPotato();
}

bool APotatoPlanterCharacter::Server_PlantPotato_Validate()
{
	return true;
}

void APotatoPlanterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APotatoPlanterCharacter::Server_PlantPotato);
}

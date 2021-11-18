// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoPlanterCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include <DrawDebugHelpers.h>

void APotatoPlanterCharacter::PlantPotato()
{
	UWorld* world = GetWorld();
	if (IsValid(world))
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

		TSubclassOf<APotato>& potatoType = _potatoTypes[FMath::RandRange(0, _potatoTypes.Num()-1)];

		APotato* newPotato = world->SpawnActor<APotato>(potatoType, potatoTransform);
		UPrimitiveComponent* potatoPrimitiveComponent = Cast<UPrimitiveComponent>(newPotato->GetRootComponent());
		potatoPrimitiveComponent->SetPhysicsLinearVelocity(randomVelocity);
	}
}

void APotatoPlanterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APotatoPlanterCharacter::PlantPotato);
}

void APotatoPlanterCharacter::Tick(float dt)
{
	Super::Tick(dt);
	if (IsPlayerControlled())
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Emerald, TEXT("Currently possessing a potato planter. Press tab to change character."), false);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Emerald, TEXT("Right click to spawn potatoes"), false);
	}
}

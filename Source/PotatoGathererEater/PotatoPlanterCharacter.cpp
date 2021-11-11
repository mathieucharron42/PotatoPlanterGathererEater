// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoPlanterCharacter.h"

#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"

void APotatoPlanterCharacter::PlantPotato()
{
	UWorld* world = GetWorld();
	if (IsValid(world))
	{
		FTransform transform = GetTransform();

		FVector location = transform.GetUnitAxis(EAxis::X) * _spawnDistance;
		FRotator rotation = UKismetMathLibrary::RandomRotator(true);

		transform.AddToTranslation(location);
		transform.ConcatenateRotation(rotation.Quaternion());

		TSubclassOf<APotato>& potatoType = _potatoTypes[FMath::RandRange(0, _potatoTypes.Num()-1)];

		APotato* newPotato = world->SpawnActor<APotato>(potatoType, transform);
	}
}

void APotatoPlanterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APotatoPlanterCharacter::PlantPotato);
}

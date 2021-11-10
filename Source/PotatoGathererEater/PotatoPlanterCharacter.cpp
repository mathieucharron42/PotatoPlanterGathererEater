// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoPlanterCharacter.h"

#include "Components/InputComponent.h"

void APotatoPlanterCharacter::Plant()
{
	UWorld* world = GetWorld();
	if (IsValid(world))
	{
		FTransform transform = GetTransform();
		APotato* newPotato = world->SpawnActor<APotato>(_potatoType, transform);
	}
}

void APotatoPlanterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APotatoPlanterCharacter::Plant);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoCheatManager.h"

#include "Potato.h"
#include "PotatoBaseCharacter.h"
#include "PotatoPlayerController.h"
#include "PotatoGameMode.h"
#include <EngineUtils.h>

void UPotatoCheatManager::SpawnPotatoes(int32 amount)
{
	UWorld* world = GetWorld();
	const APotatoPlayerController* controller = Cast<APotatoPlayerController>(GetOuterAPlayerController());
	if (ensure(IsValid(controller)))
	{
		const APotatoBaseCharacter* character = controller->GetPawn<APotatoBaseCharacter>();
		if (ensure(IsValid(character)))
		{
			APotatoGameMode* gameMode = world->GetAuthGameMode<APotatoGameMode>();
			if (IsValid(gameMode))
			{
				for (int32 i = 0; i < amount; ++i)
				{
					FTransform potatoTransform = character->GetTransform();
					float angle = ((2 * PI) / amount) * i;
					FVector offset = FVector(FMath::Cos(angle), FMath::Sin(angle), 0);
					const float radius = 150;
					potatoTransform.AddToTranslation(offset * radius);
					FVector velocity = FVector::ZeroVector;
					gameMode->SpawnPotato(potatoTransform, velocity);
				}
			}
		}
	}
}

void UPotatoCheatManager::ClearPotatoes()
{
	UWorld* world = GetWorld();
	for (TActorIterator<APotato> actorItr(world); actorItr; ++actorItr)
	{
		actorItr->Destroy();
	}
}
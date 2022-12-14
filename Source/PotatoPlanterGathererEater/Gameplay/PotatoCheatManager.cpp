#include "PotatoCheatManager.h"

#include "PotatoPlanterGathererEater/Characters/PotatoBaseCharacter.h"
#include "PotatoPlanterGathererEater/Crops/Potato.h"
#include "PotatoPlanterGathererEater/Crops/PotatoManagerSubsystem.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoPlayerController.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoGameMode.h"

#include "EngineUtils.h"

void UPotatoCheatManager::Potato_SpawnPotatoes(int32 amount)
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

void UPotatoCheatManager::Potato_ClearPotatoes()
{
	UWorld* world = GetWorld();
	if (ensure(IsValid(world)))
	{
		UGameInstance* gameInstance = world->GetGameInstance();
		if (ensure(IsValid(gameInstance)))
		{
			UPotatoManagerSubsystem* potatoSubsystem = gameInstance->GetSubsystem<UPotatoManagerSubsystem>();
			// Aussi considérer for (TActorIterator<APotato> actorItr(world); actorItr; ++actorItr) bien que plus lent
			for (APotato* potato : potatoSubsystem->GetPotatoes())
			{
				potato->Destroy();
			}
		}
	}
}

void UPotatoCheatManager::Potato_ScalePotatoes(float scale)
{
	UWorld* world = GetWorld();
	if (ensure(IsValid(world)))
	{
		UGameInstance* gameInstance = world->GetGameInstance();
		if (ensure(IsValid(gameInstance)))
		{
			UPotatoManagerSubsystem* potatoSubsystem = gameInstance->GetSubsystem<UPotatoManagerSubsystem>();
			// Aussi considérer for (TActorIterator<APotato> actorItr(world); actorItr; ++actorItr) bien que plus lent
			for (APotato* potato : potatoSubsystem->GetPotatoes())
			{
				if (ensure(IsValid(potato)))
				{
					potato->Cheat_Scale(scale);
				}
			}
		}
	}
}
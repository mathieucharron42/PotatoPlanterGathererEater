// Copyright Epic Games, Inc. All Rights Reserved.

#include "PotatoGathererEaterGameMode.h"
#include "PotatoGathererEaterCharacter.h"
#include "UObject/ConstructorHelpers.h"

APotatoGathererEaterGameMode::APotatoGathererEaterGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

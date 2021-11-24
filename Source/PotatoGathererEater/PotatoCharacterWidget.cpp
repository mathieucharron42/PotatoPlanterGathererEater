// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoCharacterWidget.h"

#include "PotatoEaterCharacter.h"
#include "PotatoGathererCharacter.h"
#include "PotatoPlayerState.h"
#include "PotatoPlayerController.h"
#include "PotatoPlanterCharacter.h"
#include "PotatoGameState.h"

void UPotatoCharacterWidget::SetTargetPlayer(APotatoPlayerController* player)
{
	_player = player;
}

void UPotatoCharacterWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FString role;
	TArray<FString> instructions;
	FColor color;
	if (ensure(IsValid(_player)))
	{
		APotatoPlayerState* playerState = _player->GetPlayerState<APotatoPlayerState>();
		if (IsValid(playerState))
		{
			if (ensure(IsValid(playerState->GetCurrentRole())))
			{
				EGameRoleType roleType = playerState->GetCurrentRole()->RoleType;
				instructions.Add("Press Tab to change character");
				if (roleType == EGameRoleType::Eater)
				{
					APotatoEaterCharacter* eaterCharacter = playerState->GetPawn<APotatoEaterCharacter>();

					color = FColor::Red;
					role = TEXT("Potato Eater");
					instructions.Add(TEXT("Move over potatoes to eat them"));
					if (IsValid(eaterCharacter))
					{
						instructions.Add(FString::Printf(TEXT("%f / %f calories"), eaterCharacter->GetCaloriesEaten(), eaterCharacter->GetCaloriesNeeded()));
					}
				}
				else if (roleType == EGameRoleType::Gatherer)
				{
					APotatoGathererCharacter* gathererCharacter = playerState->GetPawn<APotatoGathererCharacter>();

					color = FColor(141, 154, 203);
					role = TEXT("Potato Gatherer");
					instructions.Add(TEXT("Move over a potato to pick one up and right click to drop it"));
					if (IsValid(gathererCharacter))
					{
						instructions.Add(FString::Printf(TEXT("Is holding potato: %s"), gathererCharacter->IsHoldingPotato() ? TEXT("true") : TEXT("false")));
					}
				}
				else if (roleType == EGameRoleType::Planter)
				{
					role = TEXT("Potato Planter");
					instructions.Add(TEXT("Right click to spawn potatoes"));
					color = FColor::Emerald;
				}
			}
		}
	}
	SetPlayerRole(role, color);
	SetState(FString::Join(instructions, TEXT("\n")), color);

	APotatoGameState* potatoGameState = GetWorld()->GetGameState<APotatoGameState>();
	if (IsValid(potatoGameState))
	{
		if (potatoGameState->IsGameEnded())
		{
			SetCompleted();
		}
	}
}
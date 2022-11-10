#include "PotatoCharacterWidget.h"

#include "PotatoPlanterGathererEater/Characters/PotatoEaterCharacter.h"
#include "PotatoPlanterGathererEater/Characters/PotatoGathererCharacter.h"
#include "PotatoPlanterGathererEater/Characters/PotatoPlanterCharacter.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoGameState.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoPlayerController.h"
#include "PotatoPlanterGathererEater/Gameplay/PotatoPlayerState.h"

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
			APawn* pawn = playerState->GetPawn();
			if (IsValid(pawn))
			{
				EGameRoleType roleType = playerState->GetCurrentRole().GetRoleType();
				instructions.Add("Press Tab to change character");
				if (roleType == EGameRoleType::Eater)
				{
					color = FColor::Red;
					role = TEXT("Potato Eater");
				}
				else if (roleType == EGameRoleType::Gatherer)
				{
					color = FColor(141, 154, 203);
					role = TEXT("Potato Gatherer");
				}
				else if (roleType == EGameRoleType::Planter)
				{
					role = TEXT("Potato Planter");
					color = FColor::Emerald;
				}

				// Append instructions based on available behaviours
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
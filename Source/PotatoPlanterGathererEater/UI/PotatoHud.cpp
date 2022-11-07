#include "PotatoHud.h"

#include "PotatoPlanterGathererEater/Gameplay/PotatoPlayerController.h"
#include "PotatoPlanterGathererEater/UI/PotatoCharacterWidget.h"

void APotatoHud::BeginPlay()
{
	_potatoCharacterWidget = CreateWidget<UPotatoCharacterWidget>(GetWorld(), _potatoCharacterWidgetClass);
	if (ensure(_potatoCharacterWidget))
	{
		_potatoCharacterWidget->AddToViewport();
		APotatoPlayerController* controller = Cast<APotatoPlayerController>(GetOwningPlayerController());
		if (ensure(controller))
		{
			_potatoCharacterWidget->SetTargetPlayer(controller);
		}
	}
}

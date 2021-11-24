// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoHud.h"

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

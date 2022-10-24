// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PotatoCharacterWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "PotatoHud.generated.h"

UCLASS()
class POTATOPLANTERGATHEREREATER_API APotatoHud : public AHUD
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> _potatoCharacterWidgetClass;

	UPROPERTY(Transient)
	UPotatoCharacterWidget* _potatoCharacterWidget;
};

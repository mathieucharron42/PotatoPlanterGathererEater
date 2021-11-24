// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PotatoPlayerController.h"
#include "PotatoPlayerState.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "PotatoCharacterWidget.generated.h"

UCLASS()
class POTATOGATHEREREATER_API UPotatoCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTargetPlayer(APotatoPlayerController* player);

	UFUNCTION(BlueprintImplementableEvent)
	void SetPlayerRole(const FString& role, const FColor& color);

	UFUNCTION(BlueprintImplementableEvent)
	void SetState(const FString& role, const FColor& color);

	UFUNCTION(BlueprintImplementableEvent)
	void SetCompleted();

private:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(Transient)
	APotatoPlayerController* _player;
};

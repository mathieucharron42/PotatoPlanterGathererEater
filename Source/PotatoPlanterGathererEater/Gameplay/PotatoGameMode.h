// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PotatoPlayerController.h"

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "PotatoGameMode.generated.h"

class APotato;

UCLASS()
class POTATOPLANTERGATHEREREATER_API APotatoGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void Tick(float dt) override;

	bool ChangeRole(APotatoPlayerController* playerController);

private:
	virtual void RestartPlayer(AController* NewPlayer) override;
	
	APotatoBaseCharacter* FindSuitableCharacter(const TSubclassOf<APotatoBaseCharacter>& type);
	bool IsSuitableCharacter(const TSubclassOf<APotatoBaseCharacter>& type, const APotatoBaseCharacter* character);
	FPotatoGameRole GetNextRole(FPotatoGameRole current);

	UPROPERTY(EditAnywhere)
	TArray<FPotatoGameRole> _roles;
};

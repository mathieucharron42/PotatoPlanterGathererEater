// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PotatoPlayerController.h"

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "PotatoGameMode.generated.h"

UCLASS()
class POTATOGATHEREREATER_API APotatoGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	bool ChangeRole(APotatoPlayerController* playerController);

private:
	virtual void BeginPlay() override;

	APotatoBaseCharacter* FindSuitableCharacter(const TSubclassOf<APotatoBaseCharacter>& type);

	UPotatoGameRole* GetNextRole(UPotatoGameRole* current);

	UPROPERTY(Transient)
	TArray<UPotatoGameRole*> _roles;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UPotatoGameRole>> _rolesTypes;
};

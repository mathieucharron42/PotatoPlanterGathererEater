// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PotatoBaseCharacter.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "PotatoGameRole.generated.h"

UENUM()
enum class EGameRoleType
{
	Planter,
	Gatherer,
	Eater
};

UCLASS(Blueprintable, BlueprintType)
class POTATOPLANTERGATHEREREATER_API UPotatoGameRole : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	EGameRoleType RoleType;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APotatoBaseCharacter> CharacterType;
};

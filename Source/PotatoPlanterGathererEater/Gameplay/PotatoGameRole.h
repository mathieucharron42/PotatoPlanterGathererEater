#pragma once

#include "PotatoPlanterGathererEater/Characters/PotatoBaseCharacter.h"

#include "CoreMinimal.h"

#include "PotatoGameRole.generated.h"

UENUM()
enum class EGameRoleType
{
	Planter,
	Gatherer,
	Eater
};

USTRUCT()
struct POTATOPLANTERGATHEREREATER_API FPotatoGameRole
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	EGameRoleType RoleType;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APotatoBaseCharacter> CharacterType;

	bool operator==(const FPotatoGameRole& other) const
	{
		return RoleType == other.RoleType
			&& CharacterType == other.CharacterType;
	}

	bool operator!=(const FPotatoGameRole& other) const
	{
		return !(operator==(other));
	}
};

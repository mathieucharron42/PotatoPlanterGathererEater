#pragma once

#include "CoreMinimal.h"

#include "NutritionalInformations.generated.h"

USTRUCT()
struct POTATOGATHEREREATER_API FNutritionalInformations
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float ServingSize;

	UPROPERTY(EditAnywhere)
	int32 Calories;

	UPROPERTY(EditAnywhere)
	int32 Carbs;

	UPROPERTY(EditAnywhere)
	int32 Fat;

	UPROPERTY(EditAnywhere)
	int32 Proteins;
};

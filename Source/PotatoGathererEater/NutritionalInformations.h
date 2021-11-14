#pragma once

#include "CoreMinimal.h"

#include "NutritionalInformations.generated.h"

USTRUCT()
struct POTATOGATHEREREATER_API FNutritionalInformations
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 ServingSize;

	UPROPERTY(EditAnywhere)
	float Calories;

	UPROPERTY(EditAnywhere)
	float Carbs;

	UPROPERTY(EditAnywhere)
	float Fat;

	UPROPERTY(EditAnywhere)
	float Proteins;
};

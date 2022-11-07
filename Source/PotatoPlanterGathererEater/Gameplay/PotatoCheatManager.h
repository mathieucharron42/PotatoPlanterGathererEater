#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"

#include "PotatoCheatManager.generated.h"

UCLASS()
class POTATOPLANTERGATHEREREATER_API UPotatoCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
	UFUNCTION(Exec)
	void Potato_SpawnPotatoes(int32 amount);

	UFUNCTION(Exec)
	void Potato_ClearPotatoes();

	UFUNCTION(Exec)
	void Potato_ScalePotatoes(float scale);
};

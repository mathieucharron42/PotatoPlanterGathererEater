#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "PotatoManagerSubsystem.generated.h"

class APotato;

UCLASS()
class POTATOPLANTERGATHEREREATER_API UPotatoManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void RegisterPotato(APotato* potato);
	void UnregisterPotato(APotato* potato);

private:
	UPROPERTY()
	TArray<APotato*> _potatoes;
};

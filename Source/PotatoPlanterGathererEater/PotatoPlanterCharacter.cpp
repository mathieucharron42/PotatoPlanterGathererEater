// Fill out your copyright notice in the Description page of Project Settings.


#include "PotatoPlanterCharacter.h"
#include "PotatoGameMode.h"


#include "Components/InputComponent.h"
#include "DisplayDebugHelpers.h"
#include "DrawDebugHelpers.h"
#include "Engine/Canvas.h"
#include "GameFramework/MovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

static TAutoConsoleVariable<float> CVarAutoPlantPotatoRate(
	TEXT("potato.AutoPlantPotatoRate"),
	-1,
	TEXT("Rate at which planter automatically plant potato (-1 for disabled)")
);

APotatoPlanterCharacter::APotatoPlanterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APotatoPlanterCharacter::Authority_PlantPotato()
{
	if (ensure(HasAuthority()))
	{
		UWorld* world = GetWorld();
		if (IsValid(world))
		{
			APotatoGameMode* gameMode = world->GetAuthGameMode<APotatoGameMode>();
			if (ensure(IsValid(gameMode)))
			{
				FTransform planterTransform = GetTransform();

				FTransform potatoTransform = planterTransform;
				{
					FVector relativeLocation = planterTransform.GetRotation().RotateVector(_spawn);
					potatoTransform.AddToTranslation(relativeLocation);
					FRotator relativeRotation = UKismetMathLibrary::RandomRotator(true);
					potatoTransform.SetRotation(relativeRotation.Quaternion());
				}

				FVector randomVelocity = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(planterTransform.GetUnitAxis(EAxis::X), 45.f) * _spawnVelocity;
				randomVelocity.Z = FMath::Abs(randomVelocity.Z);
				//DrawDebugLine(GetWorld(), potatoTransform.GetLocation(), potatoTransform.GetLocation() + randomVelocity, FColor::Red, false, 5);

				gameMode->SpawnPotato(potatoTransform, randomVelocity);
			}
		}
	}
}

void APotatoPlanterCharacter::Server_PlantPotato_Implementation()
{
	Authority_PlantPotato();
}

bool APotatoPlanterCharacter::Server_PlantPotato_Validate()
{
	return true;
}

void APotatoPlanterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APotatoPlanterCharacter::Server_PlantPotato);
}

void APotatoPlanterCharacter::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
 	Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);
	if(IsValid(Canvas))
	{
		if (DebugDisplay.IsDisplayOn(FName("PotatoPlanterCharacter")))
		{
			DrawDebugCanvas2DLine(Canvas, FVector2D(100, 100), FVector2D(200, 200), FLinearColor::Green, 5);
		}
	}
}

void APotatoPlanterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CVarAutoPlantPotatoRate.GetValueOnGameThread() != -1)
	{
		_cheatAutoPlantNextTime -= DeltaSeconds;
		if (_cheatAutoPlantNextTime <= 0)
		{
			Server_PlantPotato();
			_cheatAutoPlantNextTime = CVarAutoPlantPotatoRate.GetValueOnGameThread();
		}
	}
}

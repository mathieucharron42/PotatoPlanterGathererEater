// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DebugDrawInWorldComponent.generated.h"

USTRUCT()
struct FDrawInWorldPointProperties
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 Size = 5;

	UPROPERTY(EditDefaultsOnly)
	FColor Color = FColor::White;

	UPROPERTY(EditDefaultsOnly)
	float Lifetime = -1.f;

	UPROPERTY(EditDefaultsOnly)
	float DepthRenderingPriority = 100.f;
};

USTRUCT()
struct FDrawInWorldBoxProperties
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FVector Size = FVector(50.f, 50.f, 50.f);

	UPROPERTY(EditDefaultsOnly)
	bool InheritRotation;

	UPROPERTY(EditDefaultsOnly)
	FColor Color = FColor::White;

	UPROPERTY(EditDefaultsOnly);
	float Thickness = 2.0f;

	UPROPERTY(EditDefaultsOnly)
	float Lifetime = -1.f;
};

USTRUCT()
struct FDrawInWorldSphereProperties
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float Radius = 50.f;

	UPROPERTY(EditDefaultsOnly)
	float NbSegments = 10;

	UPROPERTY(EditDefaultsOnly)
	FColor Color = FColor::White;

	UPROPERTY(EditDefaultsOnly);
	float Thickness = 2.0f;

	UPROPERTY(EditDefaultsOnly)
	float Lifetime = 0.f;
};

USTRUCT()
struct FDrawInWorldArrowProperties
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FVector Direction = FVector::XAxisVector;

	UPROPERTY(EditDefaultsOnly)
	bool InheritRotation = true;

	UPROPERTY(EditDefaultsOnly);
	float Lenght = 100.0f;

	UPROPERTY(EditDefaultsOnly);
	float Thickness = 2.0f;

	UPROPERTY(EditDefaultsOnly);
	float Size = 20.0f;

	UPROPERTY(EditDefaultsOnly)
	FColor Color = FColor::White;

	UPROPERTY(EditDefaultsOnly)
	float Lifetime = 0.f;
};

USTRUCT()
struct FDrawInWorldTextProperties
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FVector Position;

	UPROPERTY(EditDefaultsOnly)
	bool InheritRotation;

	UPROPERTY(EditDefaultsOnly);
	float Size = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	FString Text;

	UPROPERTY(EditDefaultsOnly)
	FColor Color = FColor::White;

	UPROPERTY(EditDefaultsOnly)
	float Lifetime = 0.f;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class POTATOGATHEREREATER_API UDebugDrawInWorldComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UDebugDrawInWorldComponent(const FObjectInitializer& ObjectInitializer);

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Debug Point", meta = (AllowPrivateAccess = true))
	bool _pointEnabled = false;

	UPROPERTY(EditDefaultsOnly, Category = "Debug Point", meta = (AllowPrivateAccess = true, EditCondition = "_pointEnabled"))
	FDrawInWorldPointProperties _pointProperties;

	UPROPERTY(EditDefaultsOnly, Category = "Debug Sphere", meta = (AllowPrivateAccess = true))
	bool _sphereEnabled = false;

	UPROPERTY(EditDefaultsOnly, Category = "Debug Sphere", meta = (AllowPrivateAccess = true, EditCondition = "_sphereEnabled"))
	FDrawInWorldSphereProperties _sphereProperties;

	UPROPERTY(EditDefaultsOnly, Category = "Debug Box", meta = (AllowPrivateAccess = true))
	bool _boxEnabled = false;

	UPROPERTY(EditDefaultsOnly, Category = "Debug Box", meta = (AllowPrivateAccess = true, EditCondition = "_boxEnabled"))
	FDrawInWorldBoxProperties _boxProperties;

	UPROPERTY(EditDefaultsOnly, Category = "Debug Arrow", meta = (AllowPrivateAccess = true))
	bool _arrowEnabled = false;

	UPROPERTY(EditDefaultsOnly, Category = "Debug Arrow", meta = (AllowPrivateAccess = true, EditCondition = "_arrowEnabled"))
	FDrawInWorldArrowProperties _arrowProperties;

	UPROPERTY(EditDefaultsOnly, Category = "Debug Text", meta = (AllowPrivateAccess = true))
	bool _textEnabled = false;

	UPROPERTY(EditDefaultsOnly, Category = "Debug Text", meta = (AllowPrivateAccess = true, EditCondition = "_textEnabled"))
	FDrawInWorldTextProperties _textProperties;
};

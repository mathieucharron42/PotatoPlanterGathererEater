// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DebugDrawInWorldComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class POTATOGATHEREREATER_API UDebugDrawInWorldComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UDebugDrawInWorldComponent(const FObjectInitializer& ObjectInitializer);

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Point Debug", meta = (AllowPrivateAccess = true))
	bool _pointEnabled = false;

	UPROPERTY(EditDefaultsOnly, Category = "Point Debug", meta = (AllowPrivateAccess = true))
	int32 _pointSize = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Point Debug", meta = (AllowPrivateAccess = true))
	FColor _pointColor = FColor::Blue;

	UPROPERTY(EditDefaultsOnly, Category = "Point Debug", meta = (AllowPrivateAccess = true))
	float _pointLifeTime = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Point Debug", meta = (AllowPrivateAccess = true))
	float _pointDepthRenderingPriority = 100.f;
};

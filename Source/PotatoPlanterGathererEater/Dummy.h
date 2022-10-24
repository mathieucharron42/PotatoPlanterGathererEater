// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dummy.generated.h"

class UDebugDrawInWorldComponent;
class USphereComponent;

UCLASS()
class POTATOPLANTERGATHEREREATER_API ADummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDebugDrawInWorldComponent* DebugDrawInWorldComponent;

	UPROPERTY(EditAnywhere)
	bool _pointEnabled = false;

	UPROPERTY(EditAnywhere)
	int32 _pointSize = 5;

	UPROPERTY(EditAnywhere)
	FColor _pointColor = FColor::White;

	UPROPERTY(EditAnywhere)
	float _pointLifeTime = 0.0f;

	UPROPERTY(EditAnywhere)
	float _pointDepthRenderingPriority = 0.0f;
};

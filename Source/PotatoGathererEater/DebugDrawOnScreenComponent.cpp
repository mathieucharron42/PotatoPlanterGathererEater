// Fill out your copyright notice in the Description page of Project Settings.

#include "DebugDrawOnScreenComponent.h"

#include "DrawDebugHelpers.h"
#include "Engine/Canvas.h"
#include "GameFramework/HUD.h"

void UDebugDrawOnScreenComponent::BeginPlay()
{
	Super::BeginPlay();	
	AHUD::OnHUDPostRender.AddUObject(this, &UDebugDrawOnScreenComponent::OnPostRender);
}

void UDebugDrawOnScreenComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	AHUD::OnHUDPostRender.RemoveAll(this);
}

void UDebugDrawOnScreenComponent::OnPostRender(AHUD* HUD, UCanvas* canvas)
{
	if (IsValid(canvas))
	{
		if (_lineEnabled)
		{
			DrawDebugCanvas2DLine(canvas, _lineProperties.Start, _lineProperties.End, _lineProperties.Color, _lineProperties.Thickness);
		}

		if (_boxEnabled)
		{
			DrawDebugCanvas2DBox(canvas, _boxProperties.Box, _boxProperties.Color, _boxProperties.Thickness);
		}

		if (_circleEnabled)
		{
			DrawDebugCanvas2DCircle(canvas, _circleProperties.Center, _circleProperties.Radius, _circleProperties.NbSide, _circleProperties.Color, _circleProperties.Thickness);
		}
	}
}


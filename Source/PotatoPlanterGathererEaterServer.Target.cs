// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class PotatoPlanterGathererEaterServerTarget : TargetRules
{
	public PotatoPlanterGathererEaterServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("PotatoPlanterGathererEater");
	}
}

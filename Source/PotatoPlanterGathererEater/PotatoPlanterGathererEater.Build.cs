// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PotatoPlanterGathererEater : ModuleRules
{
	public PotatoPlanterGathererEater(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

        if (Target.Type == TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
        }
    }
}

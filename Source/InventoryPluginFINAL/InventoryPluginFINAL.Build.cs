// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class InventoryPluginFINAL : ModuleRules
{
	public InventoryPluginFINAL(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}

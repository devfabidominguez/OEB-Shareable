// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OEB : ModuleRules
{
	public OEB(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = true;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "OnlineSubSystem", "OnlineSubsystemUtils", "Steamworks", "GameplayAbilities" });
		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");
		PrivateDependencyModuleNames.Add("JsonUtilities");
		PrivateDependencyModuleNames.Add("Json");
		PrivateDependencyModuleNames.Add("Http");
		
	}
}

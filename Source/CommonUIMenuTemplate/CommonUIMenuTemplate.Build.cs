// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CommonUIMenuTemplate : ModuleRules
{
	public CommonUIMenuTemplate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"LoadingScreen",
			"SaveSystem",
			"SPUD"
			
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"CommonGame",
			"CommonInput",
			"CommonUI",
			"GameplayTags",
			"ModularGameplay",
			"ModularGameplayActors",
			"UMG",
			"EnhancedInput",
			"Slate",
			"SlateCore", 
			"GameplayMessageRuntime"
		});
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

using UnrealBuildTool;

public class LoadingScreen : ModuleRules
{
	public LoadingScreen(ReadOnlyTargetRules Target) : base(Target)
	{
		// PublicDependencyModuleNames.AddRange(new string[] { "Slate" });
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine",
			"MoviePlayer",
			"DeveloperSettings",
			"Slate",
			"SlateCore"
		});
	}
}
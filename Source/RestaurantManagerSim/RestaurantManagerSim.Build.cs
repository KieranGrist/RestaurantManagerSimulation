using UnrealBuildTool;

public class RestaurantManagerSim : ModuleRules
{
    public RestaurantManagerSim(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // Public dependencies that are available to the module
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "EditorScriptingUtilities"
        });

        // Private dependencies that are only used by this module
        PrivateDependencyModuleNames.AddRange(new string[]
        { 
            // Add private dependencies here
        });

        // Conditional inclusion for editor builds
        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                "EditorScriptingUtilities",
                "AssetTools",        // For asset management
                "AssetRegistry",     // For asset registry operations
                "Projects"           // For project management, if needed
            });
        }

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your .uproject file with the Enabled attribute set to true
    }
}

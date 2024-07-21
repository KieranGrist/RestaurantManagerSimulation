// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RestaurantManagerSimulation : ModuleRules
{
    public RestaurantManagerSimulation(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // List public dependencies that other modules or projects might need
        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",         // Core functionality
			"CoreUObject",  // Object handling
			"Engine",       // Main engine functionalities
			"InputCore",    // Input handling
			"EnhancedInput" // Enhanced input system (if used)
		});

        // List private dependencies specific to this module
        PrivateDependencyModuleNames.AddRange(new string[]
        { 
			// Add private dependencies here if any
		});

        // Uncomment and add dependencies for Slate UI if using Slate UI framework
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment and add dependencies for online features if used
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // For OnlineSubsystemSteam, ensure it's enabled in the .uproject file
        // and also add the plugin section to the .uproject file with the Enabled attribute set to true
    }
}

// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class DDTools : ModuleRules
{
    private string ModulePath 
	{ 
		get 
		{ 
			return ModuleDirectory; 
		} 
	}

    private string ThirdPartyPath 
	{ 
		get 
		{ 
			return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty")); 
		} 
	}

    public DDTools(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "ImageWrapper",
                "RHI",
                "RenderCore",
                "UMG",
                "ContentBrowser",
				"Projects",
				"PakFile",
				"Blutility",
				"UnrealEd",
				"UMGEditor",
				"DeveloperSettings",
				"BlueprintEditorLibrary",
				"MaterialEditorTools",
				"AssetRegistry"

				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}

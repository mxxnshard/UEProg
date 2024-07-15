using UnrealBuildTool;

public class GLBProject : ModuleRules
{
    public GLBProject(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "HeadMountedDisplay",
            "UMG"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        // Assimp Library
        PublicIncludePaths.Add("C:/Users/user/Desktop/AnimationBlenderProject/GLBProject/Source/ThirdParty/Assimp/include");
        PublicAdditionalLibraries.Add("C:/Users/user/Desktop/AnimationBlenderProject/GLBProject/Source/ThirdParty/Assimp/lib/x64/assimp-vc143-mt.lib");
    }
}
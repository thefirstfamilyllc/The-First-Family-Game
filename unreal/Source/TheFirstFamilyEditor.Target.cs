using UnrealBuildTool;
using System.Collections.Generic;
public class TheFirstFamilyEditorTarget : TargetRules
{
    public TheFirstFamilyEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("TheFirstFamily");
    }
}
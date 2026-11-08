using UnrealBuildTool;
using System.Collections.Generic;
public class TheFirstFamilyTarget : TargetRules
{
    public TheFirstFamilyTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        ExtraModuleNames.Add("TheFirstFamily");
    }
}
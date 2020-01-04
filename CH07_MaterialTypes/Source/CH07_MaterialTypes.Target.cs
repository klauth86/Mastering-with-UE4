// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CH07_MaterialTypesTarget : TargetRules
{
	public CH07_MaterialTypesTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("CH07_MaterialTypes");
	}
}

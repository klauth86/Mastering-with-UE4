// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Ch06_ChangingLevelsTarget : TargetRules
{
	public Ch06_ChangingLevelsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("Ch06_ChangingLevels");
	}
}

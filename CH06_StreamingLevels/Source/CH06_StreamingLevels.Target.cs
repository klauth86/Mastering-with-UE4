// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CH06_StreamingLevelsTarget : TargetRules
{
	public CH06_StreamingLevelsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("CH06_StreamingLevels");
	}
}

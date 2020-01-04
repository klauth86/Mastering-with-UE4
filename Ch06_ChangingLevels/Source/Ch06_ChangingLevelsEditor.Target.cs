// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Ch06_ChangingLevelsEditorTarget : TargetRules
{
	public Ch06_ChangingLevelsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("Ch06_ChangingLevels");
	}
}

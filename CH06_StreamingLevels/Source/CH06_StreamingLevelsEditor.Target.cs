// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CH06_StreamingLevelsEditorTarget : TargetRules
{
	public CH06_StreamingLevelsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("CH06_StreamingLevels");
	}
}

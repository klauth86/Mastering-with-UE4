// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CH07_MaterialTypesEditorTarget : TargetRules
{
	public CH07_MaterialTypesEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("CH07_MaterialTypes");
	}
}

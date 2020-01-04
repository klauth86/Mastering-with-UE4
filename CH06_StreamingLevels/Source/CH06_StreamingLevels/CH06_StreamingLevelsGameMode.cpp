// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CH06_StreamingLevelsGameMode.h"
#include "CH06_StreamingLevelsHUD.h"
#include "CH06_StreamingLevelsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACH06_StreamingLevelsGameMode::ACH06_StreamingLevelsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACH06_StreamingLevelsHUD::StaticClass();
}

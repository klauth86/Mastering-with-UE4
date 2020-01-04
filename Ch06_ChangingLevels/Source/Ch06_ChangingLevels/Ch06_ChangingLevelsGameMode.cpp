// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Ch06_ChangingLevelsGameMode.h"
#include "Ch06_ChangingLevelsHUD.h"
#include "Ch06_ChangingLevelsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACh06_ChangingLevelsGameMode::ACh06_ChangingLevelsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	static ConstructorHelpers::FClassFinder<AHUD> HUDClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/BP_HUD"));
	HUDClass = HUDClassFinder.Class;
}

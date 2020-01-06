// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CH08_MaterialsGameMode.h"
#include "CH08_MaterialsHUD.h"
#include "CH08_MaterialsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACH08_MaterialsGameMode::ACH08_MaterialsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACH08_MaterialsHUD::StaticClass();
}

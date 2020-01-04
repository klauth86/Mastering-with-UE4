// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CH07_MaterialTypesGameMode.h"
#include "CH07_MaterialTypesHUD.h"
#include "CH07_MaterialTypesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACH07_MaterialTypesGameMode::ACH07_MaterialTypesGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ACH07_MaterialTypesHUD::StaticClass();
}

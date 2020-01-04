// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CH06_StreamingLevelsHUD.generated.h"

UCLASS()
class ACH06_StreamingLevelsHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACH06_StreamingLevelsHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};


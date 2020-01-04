// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CH07_MaterialTypesHUD.generated.h"

UCLASS()
class ACH07_MaterialTypesHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACH07_MaterialTypesHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};


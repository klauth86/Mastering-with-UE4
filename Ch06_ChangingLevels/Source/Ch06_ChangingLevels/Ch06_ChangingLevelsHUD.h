// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Ch06_ChangingLevelsHUD.generated.h"

UCLASS()
class ACh06_ChangingLevelsHUD : public AHUD
{
	GENERATED_BODY()

public:
	ACh06_ChangingLevelsHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	void BeginPlay() override;

	void InitializeWidget(class ACh06_ChangingLevelsCharacter* character);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMyUserWidget> WidgetClass;

	class UMyUserWidget* Widget;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};


// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Ch06_ChangingLevelsHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "MyUserWidget.h"

ACh06_ChangingLevelsHUD::ACh06_ChangingLevelsHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}

void ACh06_ChangingLevelsHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}

void ACh06_ChangingLevelsHUD::BeginPlay() {
	if (WidgetClass != nullptr) {
		Widget = CreateWidget<UMyUserWidget>(GetOwningPlayerController(), WidgetClass);
		checkSlow(Widget != nullptr);
		Widget->AddToViewport();

		Widget->UpdateScore();
	}
}

void ACh06_ChangingLevelsHUD::InitializeWidget(ACh06_ChangingLevelsCharacter* character) {
	if (Widget) {
		Widget->Init(character);
	}
}
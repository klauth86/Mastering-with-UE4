// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"
#include "Ch06_ChangingLevelsCharacter.h"

void UMyUserWidget::Init(ACh06_ChangingLevelsCharacter* character) {
	character->OnScoreChanged.AddUObject(this, &UMyUserWidget::UpdateScore);
}
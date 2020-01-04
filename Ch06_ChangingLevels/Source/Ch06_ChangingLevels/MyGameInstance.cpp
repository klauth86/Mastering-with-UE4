// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

static UMyGameInstance* Instance = nullptr;

UMyGameInstance* UMyGameInstance::GetInstance() {
	checkf(Instance != nullptr, TEXT("Someone is trying to use the game	instance before it has initialized!"));
		return Instance;
}

void UMyGameInstance::Init() {
	Super::Init();
	Instance = this;
	AddToRoot();
}

void UMyGameInstance::BeginDestroy() {
	ClearData();
	Super::BeginDestroy();
}

void UMyGameInstance::FinishDestroy() {
	Super::FinishDestroy();
}

void UMyGameInstance::ClearData() {
	Data = FPersistentData::EmptyData;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CH06_CHANGINGLEVELS_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UMyBlueprintFunctionLibrary();

	~UMyBlueprintFunctionLibrary();

	UFUNCTION(BlueprintCallable)
		static void LoadGameFile(FString SaveFile, UWorld* World);

	UFUNCTION(BlueprintCallable)
		static void SaveGameFile(FString SaveFile, UWorld* World);

	static void OnGameLoadedFixup(UWorld* World);

protected:

	static TArray<uint8> BinaryData;
};

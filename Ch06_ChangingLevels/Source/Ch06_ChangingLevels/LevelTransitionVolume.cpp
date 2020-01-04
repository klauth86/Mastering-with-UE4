// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransitionVolume.h"
#include "GameFramework/Pawn.h"
#include "MyGameInstance.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Paths.h"

void ALevelTransitionVolume::NotifyActorBeginOverlap(AActor* OtherActor) {
	if (auto pawn = Cast<APawn>(OtherActor)) {
		
		UWorld* World = GetWorld();

		UMyGameInstance* gameInst = UMyGameInstance::GetInstance();

		FString currentMapName = World->GetMapName();
		currentMapName.Split("UEDPIE_0_", nullptr, &currentMapName); // strip out PIE prefix if in PIE

		FString toMapName = TransitionLevel;

		FString fromFile = currentMapName + TEXT("_to_") + toMapName + TEXT(".sav");

		FString toFile = toMapName + TEXT("_to_") + currentMapName + TEXT(".sav");

		UMyBlueprintFunctionLibrary::SaveGameFile(fromFile, World);
		if (FPaths::FileExists(FPaths::ProjectSavedDir() + toFile)) {
			UMyBlueprintFunctionLibrary::LoadGameFile(toFile, World);
		}
		else {
			UGameplayStatics::OpenLevel(World, *toMapName);
		}
	}
}
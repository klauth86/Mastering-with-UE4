// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/BufferArchive.h"
#include "Serialization/MemoryReader.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "MyGameInstance.h"

TArray<uint8> UMyBlueprintFunctionLibrary ::BinaryData = TArray<uint8>();

UMyBlueprintFunctionLibrary::UMyBlueprintFunctionLibrary() {}

UMyBlueprintFunctionLibrary::~UMyBlueprintFunctionLibrary() {}

void UMyBlueprintFunctionLibrary::LoadGameFile(FString SaveFile, UWorld* World) {
	FString outPath = FPaths::ProjectSavedDir() + SaveFile;

	if (!FFileHelper::LoadFileToArray(BinaryData, *outPath)) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(FString("Game Load Failed: ") + outPath));
		return;
	}

	checkSlow(World != nullptr);

	FMemoryReader FromBinary = FMemoryReader(BinaryData, true);
	FromBinary.Seek(0);

	FPersistentData loadedData;
	FromBinary << loadedData;

	FromBinary.FlushCache();
	FromBinary.Close();

	auto gameInst = UMyGameInstance::GetInstance();
	gameInst->SetData(loadedData);

	FString mapName = loadedData.MapName.ToString();
	FString currentMapName = World->GetMapName();
	
	currentMapName.Split("UEDPIE_0_", nullptr, &currentMapName);
	if (mapName == currentMapName) {
		World->ServerTravel("?Restart", true);
	}
	else {
		UGameplayStatics::OpenLevel(World, *mapName);
	}
}

void UMyBlueprintFunctionLibrary::SaveGameFile(FString SaveFile, UWorld* World) {
	checkSlow(World != nullptr);
	
	FString outPath = FPaths::ProjectSavedDir() + SaveFile;

	FString mapName = World->GetMapName();
	mapName.Split("UEDPIE_0_", nullptr, &mapName);

	FPersistentData savedData;
	savedData.MapName = *mapName;

	UMyGameInstance* gameInst = UMyGameInstance::GetInstance();
	auto currentData = gameInst->GetData();

	savedData.Score = currentData.Score;
	savedData.LastLocation = currentData.LastLocation;

	FBufferArchive SaveData;
	SaveData << savedData;
	
	FFileHelper::SaveArrayToFile(SaveData, *outPath);
	SaveData.FlushCache();
	SaveData.Empty();
}

void UMyBlueprintFunctionLibrary::OnGameLoadedFixup(UWorld* World) {
	//if (BinaryData.Num() == 0) {
	//	checkSlow(World->GetFirstPlayerController() != nullptr);
	//	AMasteringCharacter* charPawn =
	//		Cast<AMasteringCharacter>(World->GetFirstPlayerController()->GetPawn());
	//	FixupPlayer(World, charPawn);
	//	return;
	//}
	//FMemoryReader FromBinary = FMemoryReader(BinaryData, true);
	//FromBinary.Seek(0);
	//FGameSavedData SaveGameData;
	//FromBinary << SaveGameData;
	//FromBinary.FlushCache();
	//BinaryData.Empty();
	//FromBinary.Close();
	
	//TArray<AActor*> Actors;
	//UGameplayStatics::GetAllActorsWithInterface(World,
	//	USavedActorInterface::StaticClass(), Actors);
	
	//TArray<FActorSavedData> ActorDatas = SaveGameData.SavedActors;
	//AMasteringCharacter* Char = nullptr; // if ever more than one,
	////we'll need an array and a map to their inventory
	//// iterate these arrays backwards as we will remove objects as we
	//// go, can also use iterators, but RemoveAt is simpler here for now
	//for (int i = Actors.Num() - 1; i >= 0; --i) {
	//	AActor* Actor = Actors[i];
	//	for (int j = ActorDatas.Num() - 1; j >= 0; --j) {
	//		FActorSavedData ActorRecord = ActorDatas[j];
	//		// These are actors spawned into the world that we
	//		// also found in our save data(TODO: use TArray intersection ? )
	//		if (ActorRecord.MyName == *Actor->GetName()) {
	//			FMemoryReader
	//				MemoryReader(ActorRecord.MyData, true);
	//			FSaveGameArchive Ar(MemoryReader);
	//			AMasteringCharacter* Mast =
	//				Cast<AMasteringCharacter>(Actor);
	//			if (Mast != nullptr) {
	//				Char = Mast;
	//			}
	//			Actor->Serialize(Ar);
	//			Actor->SetActorTransform(ActorRecord.MyTransform);
	//			ISavedActorInterface::Execute_ActorLoaded(Actor);
	//			APawn* pawn = Cast<APawn>(Actor);
	//			if (pawn != nullptr) {
	//				// controller needs the rotation
	//				// too as this may set the pawn's rotation once play starts
	//				AController* controller =
	//					pawn->GetController();
	//				controller->ClientSetRotation(ActorRecord.MyTransform.Rotator());
	//			}
	//			ActorDatas.RemoveAt(j);
	//			Actors.RemoveAt(i);
	//			break;
	//		}
	//	}
	//}

	//FixupPlayer(World, Char);

	//// These are actors in our save data, but not in the world, spawn them
	//for (FActorSavedData ActorRecord : ActorDatas) {
	//	FVector SpawnPos = ActorRecord.MyTransform.GetLocation();
	//	FRotator SpawnRot = ActorRecord.MyTransform.Rotator();
	//	FActorSpawnParameters SpawnParams;
	//	// if we were in a space when saved, we should be able to
	//	// spawn there again when loaded, but we could also
	//		// be overlapping an object that loaded, but will be
	//	subsequently destroyed below as it was there at level start
	//		// but not there at save time
	//		SpawnParams.SpawnCollisionHandlingOverride =
	//		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//	SpawnParams.Name = ActorRecord.MyName;
	//	UClass* SpawnClass = FindObject<UClass>(ANY_PACKAGE,
	//		*ActorRecord.MyClass);
	//	if (SpawnClass) {
	//		AActor* NewActor = GWorld->SpawnActor(SpawnClass,
	//			&SpawnPos, &SpawnRot, SpawnParams);
	//		FMemoryReader MemoryReader(ActorRecord.MyData,
	//			true);
	//		FSaveGameArchive Ar(MemoryReader);
	//		NewActor->Serialize(Ar);
	//		NewActor->SetActorTransform(ActorRecord.MyTransform);
	//		ISavedActorInterface::Execute_ActorLoaded(NewActor);
	//	}
	//}
	//// These are actors in the world that are not in our save data,
	//// destroy them(for example, a weapon pickup that was, well, picked up)
	//for (auto Actor : Actors) {
	//	Actor->Destroy();
	//}
}
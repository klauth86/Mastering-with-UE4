#include "PersistentData.h"

const FPersistentData FPersistentData::EmptyData = FPersistentData();

FPersistentData::FPersistentData(int score, FVector location, FName mapName) {
	Score = score;
	LastLocation = location;
	MapName = mapName;
}
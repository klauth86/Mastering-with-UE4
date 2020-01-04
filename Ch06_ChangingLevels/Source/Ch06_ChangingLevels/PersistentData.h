#pragma once

#include "Math/Vector.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

struct FPersistentData {

public:
	FPersistentData(int score = 0, FVector location = FVector::ZeroVector, FName mapName = FName());

	int Score;

	FVector LastLocation;

	FName MapName;

	friend FArchive& operator<<(FArchive& Ar, FPersistentData& GameData) {
		Ar << GameData.Score;
		Ar << GameData.LastLocation;
		Ar << GameData.MapName;
		return Ar;
	}

	static const FPersistentData EmptyData;
};
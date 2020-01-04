// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PersistentData.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CH06_CHANGINGLEVELS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Mastering Game Instance")
		static UMyGameInstance* GetInstance();

	virtual void Init() override;

	virtual void BeginDestroy() override;

	virtual void FinishDestroy() override;

	void ClearData();

	FORCEINLINE void Fire() { Data.Score++; }

protected:
	FPersistentData Data;

public:
	void SetData(const FPersistentData& InLoc) {
		Data = InLoc;
	}

	FORCEINLINE FPersistentData GetData() const {
		return Data;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE	int GetScore() {
		return Data.Score;
	}
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "LevelTransitionVolume.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CH06_CHANGINGLEVELS_API ALevelTransitionVolume : public ATriggerBox
{
	GENERATED_BODY()

public:
	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere)
		FString TransitionLevel;
};

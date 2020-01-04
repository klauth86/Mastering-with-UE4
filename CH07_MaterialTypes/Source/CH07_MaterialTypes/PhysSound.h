#pragma once

#include "ObjectMacros.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "PhysSound.generated.h"

USTRUCT(BlueprintType)
struct FPhysSound {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EPhysicalSurface> SurfaceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundCue* SoundCue;
};
// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CH07_MaterialTypesProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ACH07_MaterialTypesProjectile::ACH07_MaterialTypesProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ACH07_MaterialTypesProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ACH07_MaterialTypesProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{

		EPhysicalSurface surfType = SurfaceType_Default;
		if (OtherComp->GetBodyInstance() != nullptr &&
			OtherComp->GetBodyInstance()->GetSimplePhysicalMaterial() != nullptr) {
			surfType = OtherComp->GetBodyInstance()->GetSimplePhysicalMaterial()->SurfaceType;
		}
		USoundCue* cueToPlay = nullptr;
		if (ImpactSounds.Contains(surfType)) {
			cueToPlay = ImpactSounds[surfType];
		}

		const float minVelocity = 400.0f;
		if (cueToPlay != nullptr && GetVelocity().Size() > minVelocity) {
			UGameplayStatics::PlaySoundAtLocation(this, cueToPlay, Hit.Location);
		}

		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}
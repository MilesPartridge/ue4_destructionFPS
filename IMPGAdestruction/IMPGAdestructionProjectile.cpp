// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "IMPGAdestructionProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

#include "Engine/EngineTypes.h"

#include "PhysicsEngine/RadialForceComponent.h"

//#include "Kismet/GameplayStatics.h"
//#include "GameFramework/DamageType.h"

AIMPGAdestructionProjectile::AIMPGAdestructionProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AIMPGAdestructionProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;




	myRadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("AttachedRadialForce"));
	myRadialForce->SetupAttachment(RootComponent);


	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AIMPGAdestructionProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{


	myRadialForce->DestructibleDamage = 200;
	myRadialForce->ForceStrength = 200;
	myRadialForce->ImpulseStrength = 200;
	myRadialForce->Radius = 45;
	myRadialForce->Falloff = ERadialImpulseFalloff::RIF_Constant;

	myRadialForce->FireImpulse();

	Destroy();

	/*
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{

	//	OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
	//	OtherComp->AddRadialForce(GetTargetLocation(), 100, 500, RIF_Constant);
		Destroy();
	}
	*/
}
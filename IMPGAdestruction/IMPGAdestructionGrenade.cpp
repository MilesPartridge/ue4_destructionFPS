// Fill out your copyright notice in the Description page of Project Settings.


#include "IMPGAdestructionGrenade.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

#include "Engine/EngineTypes.h"

#include "PhysicsEngine/RadialForceComponent.h"

#include "Kismet/GameplayStatics.h"

#include "Engine/World.h"

//#include "Kismet/GameplayStatics.h"
//#include "GameFramework/DamageType.h"

AIMPGAdestructionGrenade::AIMPGAdestructionGrenade()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AIMPGAdestructionGrenade::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->bRotationFollowsVelocity = false;
	ProjectileMovement->bShouldBounce = false;




	myRadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("AttachedRadialForce"));
	//	myRadialForce->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	myRadialForce->SetupAttachment(RootComponent);


	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AIMPGAdestructionGrenade::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{


	myRadialForce->DestructibleDamage = 200;
	myRadialForce->ForceStrength = 2000;
	myRadialForce->ImpulseStrength = 2000;
	myRadialForce->Radius = 100;
	myRadialForce->Falloff = ERadialImpulseFalloff::RIF_Constant;

	myRadialForce->FireImpulse();

	// try and play the sound if specified
	if (GrenadeExplosionSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, GrenadeExplosionSound, GetActorLocation());
	}

	if (ExplosionFX != NULL)
	{
		UWorld* world = GetWorld();
		if (world) {
			UGameplayStatics::SpawnEmitterAtLocation(world, ExplosionFX, GetActorTransform());
		}
	}
//	UGameplayStatics::SpawnEmitterAtLocation()

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
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Particles/ParticleSystem.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IMPGAdestructionGrenade.generated.h"

UCLASS()
class IMPGADESTRUCTION_API AIMPGAdestructionGrenade : public AActor
{
GENERATED_BODY()

/** Sphere collision component */
UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
class USphereComponent* CollisionComp;

/** Projectile movement component */
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
class UProjectileMovementComponent* ProjectileMovement;


UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
class URadialForceComponent* myRadialForce;

public:
	AIMPGAdestructionGrenade();

	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }



	FORCEINLINE	class URadialForceComponent* GetRadialForce() const { return myRadialForce; }


	/** Sound to play each time we alt fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
		class USoundBase* GrenadeExplosionSound;

	/** Sound to play each time we alt fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ParticleFX)
		class UParticleSystem* ExplosionFX;


	};


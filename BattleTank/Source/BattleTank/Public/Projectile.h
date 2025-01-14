// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void Lunch(float Speed);
private:
    UProjectileMovementComponent* ProjectileMovement = nullptr;
    
    UPROPERTY(VisibleAnywhere,   Category = "Component")
    UStaticMeshComponent* CollisionMesh = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Component")
    UParticleSystemComponent* LaunchBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Component")
    UParticleSystemComponent* ImpactBlast = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Component")
    URadialForceComponent* ExplosionComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Component")
    float DestroyDelayDuration = 5;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float Damage = 33;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    UFUNCTION()
    void DestroyDelay();
};

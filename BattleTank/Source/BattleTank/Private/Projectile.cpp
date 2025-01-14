// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Components/StaticMeshComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <PhysicsEngine/RadialForceComponent.h>
#include <GameFramework/Actor.h>
#include <Engine/World.h>
#include <TimerManager.h>
#include <Kismet/GameplayStatics.h>


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
    ProjectileMovement->bAutoActivate = false;

    CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
    SetRootComponent(CollisionMesh);
    CollisionMesh->SetNotifyRigidBodyCollision(true);
    CollisionMesh->SetVisibility(true);
    CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

    LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
    LaunchBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);

    ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
    ImpactBlast->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
    ImpactBlast->bAutoActivate = false;

    ExplosionComponent = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion"));
    ExplosionComponent->AttachToComponent(CollisionMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::Lunch(float Speed)
{
    ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
    ProjectileMovement->Activate();
}


void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    LaunchBlast->Deactivate();

    ImpactBlast->Activate();

    CollisionMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
    CollisionMesh->SetVisibility(false);

    ExplosionComponent->FireImpulse();

    TArray<AActor*> IgnoreActors;
    UGameplayStatics::ApplyRadialDamage(this, Damage, GetActorLocation(), ExplosionComponent->Radius, UDamageType::StaticClass(), IgnoreActors);

    FTimerHandle DestroyTimer;
    GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AProjectile::DestroyDelay, DestroyDelayDuration, false);
}


void AProjectile::DestroyDelay()
{
    this->Destroy();
}
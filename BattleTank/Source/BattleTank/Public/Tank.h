// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankAimingComponent.h"
#include "Tank.generated.h"


class UTankBarrel;
class UTankTurretComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

    void AimAt(const FVector& HitLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
    UFUNCTION(BlueprintCallable)
    void SetBarrel(UTankBarrel* BarrelToSet);

    UFUNCTION(BlueprintCallable)
    void SetTurret(UTankTurretComponent* TurretToSet) const;

    UFUNCTION(BlueprintCallable)
    void Fire();

public:

protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

private:

    UTankBarrel* TankBarrel;

    UPROPERTY(EditAnywhere)
    float BulletLunchSpeed = 4000;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AProjectile> ProjectileBlueprint;
	
};
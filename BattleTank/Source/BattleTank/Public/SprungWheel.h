// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UStaticMeshComponent;
class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void SetupConstraint();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void AddDriveForce(float Force);

public:
    UPROPERTY(VisibleAnywhere, Category = "Components")
     USphereComponent* Axle = nullptr;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    USphereComponent* Wheel2 = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
    
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UPhysicsConstraintComponent* SpringConstraint = nullptr;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

private:
    float TotalForce = 0;
};

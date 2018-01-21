// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrackComponent : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SetThrottle(float Throttle);
	
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 40000;

private:
    UTankTrackComponent();

    void ApplySidewayForce();
    void DriveTrack();
  
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    float CurrentThrottle = 0.f;
};

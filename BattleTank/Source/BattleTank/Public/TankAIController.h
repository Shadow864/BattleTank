// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
    GENERATED_BODY()

    virtual void Tick(float DeltaTime) override;
private:
    UPROPERTY(EditDefaultsOnly)
    float AcceptanceRadius = 8000.f;


protected:
    virtual void Possess(APawn* InPawn) override;


    UFUNCTION()
    void OnPossessedTankDestroyed();

public:
};

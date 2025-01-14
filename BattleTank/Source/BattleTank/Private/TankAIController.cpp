// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "HealthComponent.h"

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AActor* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if (!PlayerTank)
        return;
    
    AActor* ControlledTank = GetPawn();

    if (!ensure(ControlledTank))
        return;

    UTankAimingComponent* AimComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    
    if (!ensure(AimComponent))
        return;

    AimComponent->AimAt(PlayerTank->GetActorLocation());
    
    if (AimComponent->GetFiringStatus() == EFiringStatus::Locked)
        AimComponent->Fire();
    
    MoveToActor(PlayerTank, AcceptanceRadius);
    
}

void ATankAIController::Possess(APawn* InPawn)
{
    Super::Possess(InPawn);

    ATank* Tank = Cast<ATank>(InPawn);

    if (ensure(Tank != nullptr))
        Tank->GetHealthComponent()->OnDie.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDestroyed);

}

void ATankAIController::OnPossessedTankDestroyed()
{
    if (!ensure(GetPawn())) { return; }

    GetPawn()->DetachFromControllerPendingDestroy();
}



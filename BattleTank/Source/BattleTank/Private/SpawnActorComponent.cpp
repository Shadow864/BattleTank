// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnActorComponent.h"
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>


// Sets default values for this component's properties
USpawnActorComponent::USpawnActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USpawnActorComponent::BeginPlay()
{
	Super::BeginPlay();
    
    SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(ActorClass, GetComponentTransform());
    
    if (SpawnedActor)
    {
        SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
    }
    
	// ...
	
}

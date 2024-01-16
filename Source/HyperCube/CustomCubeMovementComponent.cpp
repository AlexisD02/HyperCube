// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCubeMovementComponent.h"

UCustomCubeMovementComponent::UCustomCubeMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

    CurrentSpeed = NormalSpeed;
}

void UCustomCubeMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCustomCubeMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    HandleMovement(DeltaTime);
}

void UCustomCubeMovementComponent::Move(float Value)
{
    // Change speed based on input
    if (Value != 0.0f) {
        // Update the speed with direction
        CurrentSpeed = NormalSpeed * FMath::Sign(Value);
    }
}

float UCustomCubeMovementComponent::GetCurrentSpeed()
{
    return CurrentSpeed;
}

void UCustomCubeMovementComponent::HandleMovement(float DeltaTime)
{
    if (!GetOwner()) return;

    // Handle continuous movement based on the current speed
    FVector NewLocation = GetOwner()->GetActorLocation() + FVector(0.0f, CurrentSpeed * DeltaTime, 0.0f);
    GetOwner()->SetActorLocation(NewLocation);
}

void UCustomCubeMovementComponent::Jump()
{
    if (bIsJumping) return;

    // Add jump logic here
    bIsJumping = true;

    // Example jump implementation
    if (UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())) {
        MeshComp->AddImpulse(FVector(0.0f, 0.0f, JumpForce));
    }
}

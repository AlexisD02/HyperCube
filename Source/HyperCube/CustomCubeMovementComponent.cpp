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

    //HandleMovement(DeltaTime);
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

bool UCustomCubeMovementComponent::IsGrounded()
{
    FVector Start = GetOwner()->GetActorLocation();
    FVector End = Start - FVector(0.0f, 0.0f, GroundCheckDistance); // Adjust GroundCheckDistance

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner()); // Ignore the cube itself

    // Perform the raycast
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

    // Log the result
    UE_LOG(LogTemp, Warning, TEXT("IsGrounded: %s"), bHit ? TEXT("True") : TEXT("False"));

    return bHit; // Returns true if the ray hits a surface below
}


void UCustomCubeMovementComponent::Jump()
{
    if (IsGrounded()) {
        if (UStaticMeshComponent* CubeMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())) {
            CubeMesh->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, JumpForce));
        }
    }
}

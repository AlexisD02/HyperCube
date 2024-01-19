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

//bool UCustomCubeMovementComponent::IsGrounded() const
//{
//    // Get the owner and its location
//    AActor* Owner = GetOwner();
//    if (!Owner) return false;
//
//    FVector Start = Owner->GetActorLocation();
//    FVector End = Start - FVector(0.0f, 0.0f, GroundCheckDistance); // Check a short distance below the pawn
//
//    // Set up the query parameters
//    FHitResult HitResult;
//    FCollisionQueryParams QueryParams;
//    QueryParams.AddIgnoredActor(Owner); // Ignore the pawn itself
//
//    // Perform the raycast
//    return Owner->GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams);
//}

void UCustomCubeMovementComponent::Jump()
{
    //if (IsGrounded()) {
        if (UStaticMeshComponent* CubeMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent())) {
            CubeMesh->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, JumpForce));
        }
    //}
}

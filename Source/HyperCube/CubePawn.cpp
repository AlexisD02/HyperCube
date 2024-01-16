// Fill out your copyright notice in the Description page of Project Settings.


#include "CubePawn.h"
#include "CustomCubeMovementComponent.h"

ACubePawn::ACubePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    CubeMesh->SetSimulatePhysics(true);
    CubeMesh->BodyInstance.SetCollisionProfileName("Pawn");
    CubeMesh->SetNotifyRigidBodyCollision(true);
    RootComponent = CubeMesh;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 800.0f;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    CubeMovement = CreateDefaultSubobject<UCustomCubeMovementComponent>(TEXT("CubeMovement"));
}

void ACubePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateCameraPosition(DeltaTime);
}

void ACubePawn::UpdateCameraPosition(float DeltaTime)
{
    if (SpringArm != nullptr && CubeMovement) {
        // Get the current speed from the movement component
        float CurrentSpeed = CubeMovement->GetCurrentSpeed();

        // Calculate the desired offset based on movement direction
        float DesiredOffset = (CurrentSpeed > 0) ? ForwardOffset : (CurrentSpeed < 0) ? BackwardOffset : 0.0f;

        // Smoothly interpolate to the new offset
        FVector NewSocketOffset = SpringArm->SocketOffset;
        NewSocketOffset.Y = FMath::FInterpTo(SpringArm->SocketOffset.Y, DesiredOffset, DeltaTime, CameraInterpSpeed);
        SpringArm->SocketOffset = NewSocketOffset;
    }
}

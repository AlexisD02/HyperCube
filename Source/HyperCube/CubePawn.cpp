// Fill out your copyright notice in the Description page of Project Settings.


#include "CubePawn.h"
#include "CustomCubeMovementComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"

ACubePawn::ACubePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Set auto possession for the pawn to the lowest numbered player
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    CubeMesh->SetSimulatePhysics(true);
    RootComponent = CubeMesh;

    // Create a collision box component for ground detection
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent); // Attach the collision box to the root component
    CollisionBox->SetCollisionProfileName(TEXT("Pawn")); // Set collision profile

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 800.0f;

    SpringArm->bDoCollisionTest = false;

    // Disable rotation inheritance
    SpringArm->bInheritPitch = false;
    SpringArm->bInheritYaw = false;
    SpringArm->bInheritRoll = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    CubeMovement = CreateDefaultSubobject<UCustomCubeMovementComponent>(TEXT("CubeMovement"));

    bCameraDetached = false;
}

void ACubePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateCameraPosition(DeltaTime);
    HandleMovement(DeltaTime);

    if (bCameraDetached) {
        // Calculate the forward vector based on the camera's rotation
        FVector ForwardVector = Camera->GetForwardVector();
        // Move the camera continuously backwards
        Camera->AddLocalOffset(-ForwardVector * BackwardSpeed * DeltaTime);
    }
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

void ACubePawn::HandleMovement(float DeltaTime)
{
    // Get the current speed from the movement component
    float CurrentSpeed = CubeMovement->GetCurrentSpeed();

    // Handle continuous movement based on the current speed
    FVector NewLocation = GetActorLocation() + FVector(0.0f, CurrentSpeed * DeltaTime, 0.0f);
    SetActorLocation(NewLocation);
}

void ACubePawn::DetachCamera()
{
    // Check if the camera is valid
    if (Camera) {
        // Detach the camera from its parent component
        Camera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
        bCameraDetached = true;
    }
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessCubePawn.h"
#include "CustomCubeMovementComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"

AEndlessCubePawn::AEndlessCubePawn()
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
    SpringArm->SocketOffset = FVector(0.0f, SocketOffset, 0.0f);

    CubeMovement = CreateDefaultSubobject<UCustomCubeMovementComponent>(TEXT("CubeMovement"));

    bCameraDetached = false;
}

void AEndlessCubePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    HandleMovement(DeltaTime);

    if (bCameraDetached) {
        // Calculate the forward vector based on the camera's rotation
        FVector ForwardVector = Camera->GetForwardVector();
        // Move the camera continuously backwards
        Camera->AddLocalOffset(-ForwardVector * BackwardSpeed * DeltaTime);
    }
}

void AEndlessCubePawn::HandleMovement(float DeltaTime)
{
    // Handle continuous movement based on the current speed
    FVector NewLocation = GetActorLocation() + FVector(0.0f, CurrentSpeed * DeltaTime, 0.0f);
    SetActorLocation(NewLocation);
}

void AEndlessCubePawn::DetachCamera()
{
    // Check if the camera is valid
    if (Camera) {
        // Detach the camera from its parent component
        Camera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
        bCameraDetached = true;
    }
}



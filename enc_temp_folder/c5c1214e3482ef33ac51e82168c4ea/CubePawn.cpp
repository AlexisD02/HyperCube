// Fill out your copyright notice in the Description page of Project Settings.

#include "CubePawn.h"

ACubePawn::ACubePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and setup components
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    CubeMesh->BodyInstance.SetCollisionProfileName("Pawn");
    CubeMesh->SetNotifyRigidBodyCollision(true);
    RootComponent = CubeMesh;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 500.0f;
    //SpringArm->bEnableCameraLag = true;
    //SpringArm->CameraLagSpeed = 1.0f;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // Initialize default values
    CurrentSpeed = NormalSpeed;
    bIsJumping = false;
}

// Called when the game starts or when spawned
void ACubePawn::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACubePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    HandleMovement(DeltaTime);
    HandleJump();
    UpdateCameraPosition(DeltaTime);
}

// Called to bind functionality to input
void ACubePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ACubePawn::MoveForward);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACubePawn::Jump);
}

// Update camera position based on movement
void ACubePawn::UpdateCameraPosition(float DeltaTime)
{
    if (SpringArm != nullptr)
    {
        // Define the offset values for the camera
        const float ForwardOffset = 80.0f; // Adjust as needed
        const float BackwardOffset = -80.0f; // Adjust as needed

        // Calculate the desired offset based on movement direction
        float DesiredOffset = (CurrentSpeed > 0) ? ForwardOffset : (CurrentSpeed < 0) ? BackwardOffset : 0.0f;

        // Smoothly interpolate to the new offset
        FVector NewSocketOffset = SpringArm->SocketOffset;
        NewSocketOffset.Y = FMath::FInterpTo(SpringArm->SocketOffset.Y, DesiredOffset, DeltaTime, 5.0f);
        SpringArm->SocketOffset = NewSocketOffset;
    }
}

// Handle forward movement
void ACubePawn::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        // Adjust CurrentSpeed to PressedSpeed when moving forward or backward
        CurrentSpeed = PressedSpeed * FMath::Sign(Value);
    }
}

// Handle jump input
void ACubePawn::Jump()
{
    if (!bIsJumping && CubeMesh->IsSimulatingPhysics())
    {
        bIsJumping = true;
    }
}

// Handle movement logic
void ACubePawn::HandleMovement(float DeltaTime)
{
    // Apply continuous movement based on the current speed
    FVector NewLocation = GetActorLocation();
    NewLocation.Y += CurrentSpeed * DeltaTime;
    SetActorLocation(NewLocation);
}

// Handle jump logic
void ACubePawn::HandleJump()
{
    if (bIsJumping)
    {
        CubeMesh->AddImpulse(FVector(0.0f, 0.0f, JumpForce));
        bIsJumping = false;
    }
}

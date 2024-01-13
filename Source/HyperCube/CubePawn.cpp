// Fill out your copyright notice in the Description page of Project Settings.


#include "CubePawn.h"

ACubePawn::ACubePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and setup components
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));

    /*! We need it since we want to make it's physics to be able to jump/double jump !
    ! Problem is it disables the collision with any shape/object ! */
    //CubeMesh->SetSimulatePhysics(true);

    CubeMesh->BodyInstance.SetCollisionProfileName("Pawn");
    CubeMesh->SetNotifyRigidBodyCollision(true);
    RootComponent = CubeMesh;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 500.0f;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

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
    if (SpringArm != nullptr) {
        // Calculate the desired offset based on movement direction
        float DesiredOffset = (CurrentSpeed > 0) ? ForwardOffset : (CurrentSpeed < 0) ? BackwardOffset : 0.0f;

        // Smoothly interpolate to the new offset
        FVector NewSocketOffset = SpringArm->SocketOffset;
        NewSocketOffset.Y = FMath::FInterpTo(SpringArm->SocketOffset.Y, DesiredOffset, DeltaTime, CameraInterpSpeed);
        SpringArm->SocketOffset = NewSocketOffset;
    }
}

// Handle forward movement
void ACubePawn::MoveForward(float Value)
{
    CurrentSpeed = (Value != 0.0f) ? PressedSpeed * FMath::Sign(Value) : CurrentSpeed;
}

// Handle jump input
void ACubePawn::Jump()
{
    if (!bIsJumping && CubeMesh->IsSimulatingPhysics()) {
        CubeMesh->AddImpulse(FVector(0.0f, 0.0f, JumpForce));
        bIsJumping = true;
    }
}

// Handle movement logic
void ACubePawn::HandleMovement(float DeltaTime)
{
    // Apply continuous movement based on the current speed
    FVector NewLocation = GetActorLocation() + FVector(0.0f, CurrentSpeed * DeltaTime, 0.0f);
    SetActorLocation(NewLocation);
}

// Handle jump logic
void ACubePawn::HandleJump()
{
    if (bIsJumping) {
        bIsJumping = false;
    }
}

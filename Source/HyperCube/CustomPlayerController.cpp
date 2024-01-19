// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "CustomCubeMovementComponent.h"
#include "CubePawn.h"

void ACustomPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Initialize MyPawn
    CubePawn = Cast<ACubePawn>(GetPawn());
}

void ACustomPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    check(InputComponent);

    // Bind MoveForward action
    InputComponent->BindAxis("MoveForward", this, &ACustomPlayerController::CallMove);

    // Bind Jump action
    InputComponent->BindAction("Jump", IE_Pressed, this, &ACustomPlayerController::CallJump);
}

void ACustomPlayerController::CallMove(float Value)
{
    if (CubePawn) {
        // Call the pawn's movement function
        CubePawn->CubeMovement->Move(Value);
    }
}

void ACustomPlayerController::CallJump()
{
    if (CubePawn) {
        //CubePawn->HandleJump();
        // Call the pawn's jump function
        CubePawn->CubeMovement->Jump();
    }
}



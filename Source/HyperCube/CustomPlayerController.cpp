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

    // Bind Dash action
    InputComponent->BindAction("Dash", IE_Pressed, this, &ACustomPlayerController::CallDash);

    // Bind Jump action
    InputComponent->BindAction("GroundSlam", IE_Pressed, this, &ACustomPlayerController::CallGroundSlam);
}

void ACustomPlayerController::CallMove(float Value)
{
    if (CubePawn) {
        // Call the pawn's movement function
        CubePawn->CubeMovement->Move(Value);
        //CubePawn->CubeMovement->DirectionSign = abs(CubePawn->CubeMovement->DirectionSign);
        //CubePawn->CubeMovement->DirectionSign *= Value;
    }
}

void ACustomPlayerController::CallJump()
{
    if (CubePawn) {
        // Call the pawn's jump function
        CubePawn->CubeMovement->Jump();
    }
}

void ACustomPlayerController::CallDash()
{
    if (CubePawn) {
        // Call the pawn's dash function
        CubePawn->CubeMovement->Dash();
    }
}

void ACustomPlayerController::CallGroundSlam()
{
    if (CubePawn) 
    {
        // Call the pawn's ground slam function
        CubePawn->CubeMovement->GroundSlam();
    }
}
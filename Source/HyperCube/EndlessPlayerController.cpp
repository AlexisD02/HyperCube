// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessPlayerController.h"
#include "CustomCubeMovementComponent.h"
#include "EndlessCubePawn.h"
#include "Blueprint/UserWidget.h"


void AEndlessPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Initialize MyPawn
    CubePawn = Cast<AEndlessCubePawn>(GetPawn());

    F_MainGameWidget();
}

void AEndlessPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    check(InputComponent);

    // Bind Jump action
    InputComponent->BindAction("Jump", IE_Pressed, this, &AEndlessPlayerController::CallJump);

    // Bind Dash action
    InputComponent->BindAction("Dash", IE_Pressed, this, &AEndlessPlayerController::CallDash);

    // Bind Jump action
    InputComponent->BindAction("GroundSlam", IE_Pressed, this, &AEndlessPlayerController::CallGroundSlam);

    InputComponent->BindAction("Pause", IE_Pressed, this, &AEndlessPlayerController::PauseMenu);
}

void AEndlessPlayerController::CallJump()
{
    if (CubePawn) {
        // Call the pawn's jump function
        CubePawn->CubeMovement->Jump();
    }
}

void AEndlessPlayerController::CallDash()
{
    if (CubePawn) {
        // Call the pawn's dash function
        CubePawn->CubeMovement->Dash();
    }
}

void AEndlessPlayerController::CallGroundSlam()
{
    if (CubePawn) {
        // Call the pawn's ground slam function
        CubePawn->CubeMovement->GroundSlam();
    }
}

void AEndlessPlayerController::F_MainGameWidget()
{
    if (MainGameWidgetClass) {
        MainGameWidget = CreateWidget(this, MainGameWidgetClass);
        if (MainGameWidget) {
            MainGameWidget->AddToViewport();
        }
    }
}


void AEndlessPlayerController::PauseMenu()
{
    if (!PauseMenuWidget && PauseMenuWidgetClass) {
        // Create the pause menu widget if it doesn't exist
        PauseMenuWidget = CreateWidget(this, PauseMenuWidgetClass);
    }

    if (PauseMenuWidget) {
        // Add the widget to the viewport and pause the game
        PauseMenuWidget->AddToViewport();
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
        SetPause(true);
    }
}

void AEndlessPlayerController::GameOverScreen()
{
    if (!GameOverScreenWidget && GameOverScreenWidgetClass) {
        // Create the pause menu widget if it doesn't exist
        GameOverScreenWidget = CreateWidget(this, GameOverScreenWidgetClass);
    }

    if (GameOverScreenWidget) {
        // Add the widget to the viewport and pause the game
        GameOverScreenWidget->AddToViewport();
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
        SetPause(true);
    }
}

void AEndlessPlayerController::WinScreen()
{
    if (!WinScreenWidget && WinScreenWidgetClass) {
        // Create the pause menu widget if it doesn't exist
        WinScreenWidget = CreateWidget(this, WinScreenWidgetClass);
    }

    if (WinScreenWidget) {
        // Add the widget to the viewport and pause the game
        WinScreenWidget->AddToViewport();
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
        SetPause(true);
    }
}


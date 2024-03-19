// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerForBossLevel.h"
//#include "CustomCubeMovementComponent.h"
//#include "CubePawn.h"
//#include "Blueprint/UserWidget.h"

//void APlayerControllerForBossLevel::BeginPlay()
//{
//    Super::BeginPlay();
//
//    // Initialize MyPawn
//    CubePawn = Cast<ACubePawn>(GetPawn());
//
//    F_MainGameWidget();
//}
//
//void APlayerControllerForBossLevel::SetupInputComponent()
//{
//    Super::SetupInputComponent();
//
//    check(InputComponent);
//
//    // Bind MoveForward action
//    InputComponent->BindAxis("MoveForward", this, &ACustomPlayerController::CallMove);
//
//    // Bind Jump action
//    InputComponent->BindAction("Jump", IE_Pressed, this, &ACustomPlayerController::CallJump);
//
//    // Bind Dash action
//    InputComponent->BindAction("Dash", IE_Pressed, this, &ACustomPlayerController::CallDash);
//
//    // Bind Jump action
//    InputComponent->BindAction("GroundSlam", IE_Pressed, this, &ACustomPlayerController::CallGroundSlam);
//
//    InputComponent->BindAction("Pause", IE_Pressed, this, &ACustomPlayerController::PauseMenu);
//}
//
//void APlayerControllerForBossLevel::CallMove(float Value)
//{
//    if (CubePawn) {
//        // Call the pawn's movement function
//        CubePawn->CubeMovement->Move(Value);
//        //CubePawn->CubeMovement->DirectionSign = abs(CubePawn->CubeMovement->DirectionSign);
//        //CubePawn->CubeMovement->DirectionSign *= Value;
//    }
//}
//
//void APlayerControllerForBossLevel::CallJump()
//{
//    if (CubePawn) {
//        // Call the pawn's jump function
//        CubePawn->CubeMovement->Jump();
//    }
//}
//
//void APlayerControllerForBossLevel::CallDash()
//{
//    if (CubePawn) {
//        // Call the pawn's dash function
//        CubePawn->CubeMovement->Dash();
//    }
//}
//
//void APlayerControllerForBossLevel::CallGroundSlam()
//{
//    if (CubePawn) {
//        // Call the pawn's ground slam function
//        CubePawn->CubeMovement->GroundSlam();
//    }
//}
//
//void APlayerControllerForBossLevel::F_MainGameWidget()
//{
//    if (MainGameWidgetClass) {
//        MainGameWidget = CreateWidget(this, MainGameWidgetClass);
//        if (MainGameWidget) {
//            MainGameWidget->AddToViewport();
//        }
//    }
//}
//
//void APlayerControllerForBossLevel::F_BossHealthWidget()
//{
//    if (BossHealthWidgetClass) {
//        BossHealthWidget = CreateWidget(this, BossHealthWidgetClass);
//        if (BossHealthWidget) {
//            BossHealthWidget->AddToViewport();
//        }
//    }
//}
//
//void APlayerControllerForBossLevel::PauseMenu()
//{
//    if (!PauseMenuWidget && PauseMenuWidgetClass) {
//        // Create the pause menu widget if it doesn't exist
//        PauseMenuWidget = CreateWidget(this, PauseMenuWidgetClass);
//    }
//
//    if (PauseMenuWidget) {
//        // Add the widget to the viewport and pause the game
//        PauseMenuWidget->AddToViewport();
//        SetInputMode(FInputModeUIOnly());
//        bShowMouseCursor = true;
//        SetPause(true);
//    }
//}
//
//void APlayerControllerForBossLevel::GameOverScreen()
//{
//    if (!GameOverScreenWidget && GameOverScreenWidgetClass) {
//        // Create the pause menu widget if it doesn't exist
//        GameOverScreenWidget = CreateWidget(this, GameOverScreenWidgetClass);
//    }
//
//    if (GameOverScreenWidget) {
//        // Add the widget to the viewport and pause the game
//        GameOverScreenWidget->AddToViewport();
//        SetInputMode(FInputModeUIOnly());
//        bShowMouseCursor = true;
//        SetPause(true);
//    }
//}
//
//void APlayerControllerForBossLevel::WinScreen()
//{
//    if (!WinScreenWidget && WinScreenWidgetClass) {
//        // Create the pause menu widget if it doesn't exist
//        WinScreenWidget = CreateWidget(this, WinScreenWidgetClass);
//    }
//
//    if (WinScreenWidget) {
//        // Add the widget to the viewport and pause the game
//        WinScreenWidget->AddToViewport();
//        SetInputMode(FInputModeUIOnly());
//        bShowMouseCursor = true;
//        SetPause(true);
//    }
//}
//

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EndlessCubePawn.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EndlessPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HYPERCUBE_API AEndlessPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    // Bind player input to actions and axes
    virtual void SetupInputComponent() override;

    AEndlessCubePawn* CubePawn;

    // Function to handle jump input
    void CallJump();

    // Function to handle dash input
    void CallDash();

    // Function to handle dash input
    void CallGroundSlam();

    void PauseMenu();

    void GameOverScreen();

    void WinScreen();

    UFUNCTION()
    void F_MainGameWidget();

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> MainGameWidgetClass;

    UPROPERTY()
    UUserWidget* MainGameWidget;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> PauseMenuWidgetClass;

    UPROPERTY()
    UUserWidget* PauseMenuWidget;


    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> GameOverScreenWidgetClass;

    UPROPERTY()
    UUserWidget* GameOverScreenWidget;

    // Reference to the pause menu widget class
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> WinScreenWidgetClass;

    //// The actual instance of the pause menu widget
    UPROPERTY()
    UUserWidget* WinScreenWidget;

protected:
    virtual void BeginPlay() override;
};

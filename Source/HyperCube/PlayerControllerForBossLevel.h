// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CubePawn.h"
#include "Blueprint/UserWidget.h"
#include "PlayerControllerForBossLevel.generated.h"

/**
 * 
 */
UCLASS()
class HYPERCUBE_API APlayerControllerForBossLevel : public APlayerController
{
	GENERATED_BODY()

public:
    // Bind player input to actions and axes
    virtual void SetupInputComponent() override;

    ACubePawn* CubePawn;

    // Function to handle forward movement input
    void CallMove(float Value);

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

    UFUNCTION()
    void F_BossHealthWidget();

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

    // Reference to the win menu widget class
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> WinScreenWidgetClass;

    // The actual instance of the win menu widget
    UPROPERTY()
    UUserWidget* WinScreenWidget;

    // Reference to the boss health widget class
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UUserWidget> BossHealthWidgetClass;

    // The actual instance of the boss health widget
    UPROPERTY()
    UUserWidget* BossHealthWidget;

protected:
    virtual void BeginPlay() override;
};

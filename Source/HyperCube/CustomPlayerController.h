// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CubePawn.h"
#include "GameFramework/PlayerController.h"
#include "CustomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HYPERCUBE_API ACustomPlayerController : public APlayerController
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

protected:
    virtual void BeginPlay() override;
};

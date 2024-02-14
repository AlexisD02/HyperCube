// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomCubeMovementComponent.generated.h"

class ADefaultLevelGameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HYPERCUBE_API UCustomCubeMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UCustomCubeMovementComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Function to handle movement input
    void Move(float Value);

    // Function to handle jump input
    void Jump();

    void Dash();

    void GroundSlam();

    float GetCurrentSpeed();

    bool IsGrounded();

    // When you get the power-up, this becomes true, letting the player double jump.
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        bool bCanDoubleJump = true;

    // When you get the power-up, this becomes true, letting the player dash.
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        bool bCanDash = true;

    // When you get the power-up, this becomes true, letting the player ground slam.
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
        bool bCanGroundSlam = true;

    // Functions to be called in order to change the above bools to true.
    UFUNCTION()
        void EnableDoubleJump();

    UFUNCTION()
        void EnableDash();

    UFUNCTION()
        void EnableGroundSlam();

    // Used for the double jump functionality
    UPROPERTY(VisibleAnywhere)
        bool hasJumped = false;

    UPROPERTY(VisibleAnywhere)
        float DirectionSign = 1.0f;

private:
    // Speed properties
    UPROPERTY(EditAnywhere)
    float NormalSpeed = 700.0f;

    // Current movement speed
    float CurrentSpeed = 0.0f;

    // Jump force
    UPROPERTY(EditAnywhere)
    float JumpForce = 1300.0f;

    // Dash force
    UPROPERTY(EditAnywhere)
    float DashForce = 1300.0f;

    // Dash force
    UPROPERTY(EditAnywhere)
    float GroundSlamForce = 1300.0f;

    // Adjust this value based on testing
    UPROPERTY(EditAnywhere)
    float GroundCheckDistance = 100.0f; 

    UPROPERTY()
        ADefaultLevelGameModeBase* GameModeRef;
};

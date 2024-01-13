// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "CubePawn.generated.h"

UCLASS()
class HYPERCUBE_API ACubePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACubePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

    // Speed at which the camera moves to its new position
    UPROPERTY(EditAnywhere, Category = "Camera")
    float CameraInterpSpeed = 3.0f;

    // Define the offset values for the camera
    UPROPERTY(EditAnywhere, Category = "Camera")
    float ForwardOffset = 230.0f; // Adjust as needed

    UPROPERTY(EditAnywhere, Category = "Camera")
    float BackwardOffset = -230.0f; // Adjust as needed

    // Movement speed of the pawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float Speed = 400.0f;

    // Jump force of the pawn
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float JumpForce = 500.0f;

    // Normal movement speed of the pawn (when no key is pressed)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float CurrentSpeed = 400.0f;

    // Increased movement speed of the pawn (when a key is pressed)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float PressedSpeed = 600.0f;

private:
    // Handle forward movement
    void MoveForward(float Value);

    // Handle jump input
    void Jump();

    // Handle movement logic
    void HandleMovement(float DeltaTime);

    // Handle jump logic
    void HandleJump();

    void UpdateCameraPosition(float DeltaTime);

    // Static Mesh Component for the Cube
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CubeMesh;

    // Spring Arm for camera distance and angle
    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    // Camera Component
    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

    // Direction of forward movement (-1 for backward, 1 for forward, 0 for stop)
    int32 MovementDirection = 0;

    // Indicates whether the pawn is currently jumping
    bool bIsJumping = false;
};
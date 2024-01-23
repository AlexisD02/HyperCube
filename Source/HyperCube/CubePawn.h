// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CustomCubeMovementComponent.h"
#include "Camera/CameraComponent.h"

#include "CubePawn.generated.h"

UCLASS()
class HYPERCUBE_API ACubePawn : public APawn
{
	GENERATED_BODY()

public:
    ACubePawn();

    UPROPERTY(VisibleAnywhere)
    UCustomCubeMovementComponent* CubeMovement;

    void UpdateCameraPosition(float DeltaTime);

    void HandleMovement(float DeltaTime);

protected:
    virtual void Tick(float DeltaTime) override;

    // Speed at which the camera moves to its new position
    UPROPERTY(EditAnywhere, Category = "Camera")
    float CameraInterpSpeed = 3.0f;

    // Define the offset values for the camera
    UPROPERTY(EditAnywhere, Category = "Camera")
    float ForwardOffset = 330.0f; // Adjust as needed

    UPROPERTY(EditAnywhere, Category = "Camera")
    float BackwardOffset = -330.0f; // Adjust as needed

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CubeMesh;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

    // Jump force
    UPROPERTY(EditAnywhere)
    float JumpForce = 400.0f;

};

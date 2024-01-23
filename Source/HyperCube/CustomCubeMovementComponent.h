// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomCubeMovementComponent.generated.h"


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

    float GetCurrentSpeed();

    bool IsGrounded();

private:
    // Speed properties
    UPROPERTY(EditAnywhere)
    float NormalSpeed = 700.0f;

    // Current movement speed
    float CurrentSpeed = 0.0f;

    // Jump force
    UPROPERTY(EditAnywhere)
    float JumpForce = 1300.0f;

    float GroundCheckDistance = 100.0f; // Adjust this value based on testing

};

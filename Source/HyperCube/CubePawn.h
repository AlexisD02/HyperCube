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

	// Speed of the cube
	UPROPERTY(EditAnywhere)
	float Speed = 400.0f;

private:
	// Static Mesh Component for the Cube
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	// Spring Arm for camera distance and angle
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	// Camera Component
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	// Forward movement function
	void MoveForward(float Value);

	float CurrentForwardMovement;

};

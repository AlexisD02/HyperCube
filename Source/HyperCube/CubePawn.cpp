// Fill out your copyright notice in the Description page of Project Settings.


#include "CubePawn.h"

// Sets default values
ACubePawn::ACubePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Set default values for this pawn's properties
    CurrentForwardMovement = 0.0f;

    // Create and attach the static mesh component.
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;

    // Create and attach the spring arm component.
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(CubeMesh);
    SpringArm->TargetArmLength = 500.0f; // Adjust the camera distance
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 3.0f;

    // Create and attach the camera component.
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ACubePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACubePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Current location
    FVector NewLocation = GetActorLocation();

    // Update location based on speed and input
    NewLocation.Y += CurrentForwardMovement * Speed * DeltaTime;

    // Set the updated location
    SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void ACubePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind the move forward function to an axis
    PlayerInputComponent->BindAxis("MoveForward", this, &ACubePawn::MoveForward);
}

void ACubePawn::MoveForward(float Value)
{
    CurrentForwardMovement = Value;
}

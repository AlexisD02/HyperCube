// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCubeMovementComponent.h"
#include "DefaultLevelGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UCustomCubeMovementComponent::UCustomCubeMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

    CurrentSpeed = NormalSpeed;
}

void UCustomCubeMovementComponent::BeginPlay()
{
	Super::BeginPlay();

    // Get a reference to the level gamemode base
    GameModeRef = Cast<ADefaultLevelGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
    bCanDoubleJump = false;
    bCanDash = false;
    bCanGroundSlam = false;
}

void UCustomCubeMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //HandleMovement(DeltaTime);
}

void UCustomCubeMovementComponent::Move(float Value)
{
    // Change speed based on input
    if (Value != 0.0f) {
        // Update the speed with direction
        CurrentSpeed = NormalSpeed * FMath::Sign(Value);
    }
}

float UCustomCubeMovementComponent::GetCurrentSpeed()
{
    return CurrentSpeed;
}

bool UCustomCubeMovementComponent::IsGrounded()
{
    FVector Start = GetOwner()->GetActorLocation();
    FVector End = Start - FVector(0.0f, 0.0f, GroundCheckDistance); // Adjust GroundCheckDistance

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner()); // Ignore the cube itself

    // Perform the raycast
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

    // Log the result
    UE_LOG(LogTemp, Warning, TEXT("IsGrounded: %s"), bHit ? TEXT("True") : TEXT("False"));

    if (bHit) bHasDashed = false;

    return bHit; // Returns true if the ray hits a surface below
}

void UCustomCubeMovementComponent::EnableDoubleJump()
{
    bCanDoubleJump = true;
}

void UCustomCubeMovementComponent::EnableDash()
{
    bCanDash = true;
}

void UCustomCubeMovementComponent::EnableGroundSlam()
{
    bCanGroundSlam = true;
}


void UCustomCubeMovementComponent::Jump()
{
    UStaticMeshComponent* CubeMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    if (IsGrounded()) {
        if (CubeMesh)
        {
            CubeMesh->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, JumpForce));
            hasJumped = false;

            FRotator Rotation = CubeMesh->GetComponentRotation();
            Rotation.Pitch += 90.0f;

            CubeMesh->SetWorldRotation(Rotation);
        }
    }
    else 
    {
        if (bCanDoubleJump)  // Check if we have the double jump power up
        {
            if (CubeMesh)
            {
                if (!hasJumped)
                {
                    CubeMesh->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, JumpForce));
                    hasJumped = true;
                }
            }
        }
    }
}


void UCustomCubeMovementComponent::Dash()
{
    if (bCanDash)  // Check if we have the dash power up
    {
        UStaticMeshComponent* CubeMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

        if (!IsGrounded())
        {
            if (CubeMesh)
            {                                       
                if (!bHasDashed) {
                    CubeMesh->SetPhysicsLinearVelocity(FVector(0.0f, DashForce * FMath::Sign(CurrentSpeed), 0.0f));
                    bHasDashed = true;
                }
            }
        }
    }
}

void UCustomCubeMovementComponent::GroundSlam()
{
    if (bCanGroundSlam)  // Check if we have the ground slam power up
    {
        UStaticMeshComponent* CubeMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

        if (!IsGrounded())
        {
            if (CubeMesh)
            {
                UE_LOG(LogTemp, Warning, TEXT("Enetered ground slam"));
                CubeMesh->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, -GroundSlamForce));
                //Cube->AddImpulse(FVector(GroundSlamForce, 0.0f, 0.0f));

                //UBoxComponent* CollisionBox = CubeMesh->CollisionBox;
                //if (CollisionBox)
                //{
                //    FVector SlamImpulse = FVector(0.f, 0.f, -10000.f); // Adjust the impulse strength as needed
                //    CollisionBox->AddImpulse(SlamImpulse);
                //}
            }
        }
    }
}

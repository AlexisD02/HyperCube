// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserEnemy.generated.h"

UCLASS()
class HYPERCUBE_API ALaserEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LaserEnemyMesh;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 100.0f;

		//** Patrol
		UFUNCTION()
		void Patrol(float DeltaTime);

		UPROPERTY(VisibleAnywhere)
		bool bShouldInitiatePatrol = true;

		UPROPERTY(EditAnywhere)
		float PatrolDistance = 10.0f;

		FTimerHandle PatrolTimer;

		UPROPERTY(EditAnywhere)
		float PatrolDuration = 3.0f;

		// Sets up the patrol by changing the direction of the enemy
		UFUNCTION()
		void InitiatePatrol();

		// Function to run when the timer runs out. It makes bShouldPatrol to true 
		UFUNCTION()
		void EnablePatrol();

		//** Laser Fire

		// The raycast function that simulates the laser fire result
		UFUNCTION()
		void LaserFire();

		UPROPERTY(VisibleAnywhere)
		bool bCanFire = true;

		FTimerHandle LaserTimer;

		UPROPERTY(EditAnywhere)
		float RPM = 3.0f;

		UPROPERTY(EditAnywhere)
		float LaserDistance = 1000.0f;

		// Function to run when the timer runs out. It makes bCanFire to true 
		UFUNCTION()
		void EnableFire();
};

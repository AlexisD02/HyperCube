// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserEnemy.generated.h"

class UBoxComponent;
class ABossGameModeBase;

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

	// Collision box to detect when the player can damage the enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* TakeDamageBox;

	// Collision box to detect when the player can get damaged by the enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* DealDamageBoxLeft;
	// Collision box to detect when the player can get damaged by the enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* DealDamageBoxRight;

	UFUNCTION()
	void DealDamageToPlayerEventLeft(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void DealDamageToPlayerEventRight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void TakeDamageEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* LaserEnemyMesh;

		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
			AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
		float MovementSpeed = 100.0f;

		//** Patrol
		UFUNCTION()
		void Patrol(float DeltaTime);

		// Can be toogled true or false, so you can choose if the enemy can patrol or not.
		UPROPERTY(EditAnywhere)
		bool bCanPatrol = true;

		// Is used for the patrol to work. Do NOT change.
		UPROPERTY()
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

		// Can be toogled true or false, so you can choose if the enemy can fire or not.
		UPROPERTY(EditAnywhere)
		bool bShouldFire = true;

		UPROPERTY(EditAnywhere)
		bool bShouldFireAtPlayer = false;

		// Is used for the fire to work. Do NOT change.
		UPROPERTY()
		bool bCanFire = true;

		FTimerHandle LaserTimer;

		FTimerHandle LaserLineTimer;

		UPROPERTY(EditAnywhere)
		float RPM = 5.0f;

		UPROPERTY(EditAnywhere)
		float laserDuration = 1.0f;

		// Function to run when the timer runs out. It makes bCanFire to true 
		UFUNCTION()
		void RemoveLaser();

		UPROPERTY(EditAnywhere)
		float LaserDistance = 1000.0f;

		// Function to run when the timer runs out. It makes bCanFire to true 
		UFUNCTION()
		void EnableFire();

		// Static mesh component to represent the laser
		UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* LaserLineMesh;

		//**

		UPROPERTY()
		ABossGameModeBase* GameModeRef;
};

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

	UPROPERTY(EditAnywhere)
		bool shouldPatrol = false;

	UPROPERTY(EditAnywhere)
		float patrolDistance = 10.0f;



	void Patrol();
};

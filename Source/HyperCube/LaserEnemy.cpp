// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserEnemy.h"

// Sets default values
ALaserEnemy::ALaserEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaserEnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserEnemyMesh"));
	LaserEnemyMesh->SetSimulatePhysics(true);
	RootComponent = LaserEnemyMesh;
}

// Called when the game starts or when spawned
void ALaserEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (shouldPatrol) Patrol();
}

void Patrol()
{
	// Handle continuous movement based on the current speed
	//FVector NewLocation = GetActorLocation() + FVector(0.0f, MovementSpeed * DeltaTime, 0.0f);
	//SetActorLocation(NewLocation);
}


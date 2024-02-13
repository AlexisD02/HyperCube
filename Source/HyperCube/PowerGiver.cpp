// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerGiver.h"

// Sets default values
APowerGiver::APowerGiver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerGiverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PowerGiverMesh"));
	SetRootComponent(PowerGiverMesh);

}

// Called when the game starts or when spawned
void APowerGiver::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerGiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


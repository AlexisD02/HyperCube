// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeActor.h"

// Sets default values
ASpikeActor::ASpikeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpikeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpikeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultLevelGameModeBase.h"

void ADefaultLevelGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Default"));
}

void ADefaultLevelGameModeBase::PointScored()
{

	pointsScored += 1.0f;
	UE_LOG(LogTemp, Warning, TEXT("Points: %f"), pointsScored);
}

// Copyright Epic Games, Inc. All Rights Reserved.


#include "HyperCubeGameModeBase.h"

void AHyperCubeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Default"));
}

void AHyperCubeGameModeBase::PointScored()
{
	pointsScored++;
	UE_LOG(LogTemp, Warning, TEXT("Points: %f"), pointsScored);
}

int AHyperCubeGameModeBase::GetPointScored()
{
	return pointsScored;
}

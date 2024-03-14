// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessGameModeBase.h"

void AEndlessGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Default"));
}

void AEndlessGameModeBase::PointScored()
{
	pointsScored++;
	UE_LOG(LogTemp, Warning, TEXT("Points: %f"), pointsScored);
}

int AEndlessGameModeBase::GetPointScored()
{
	return pointsScored;
}

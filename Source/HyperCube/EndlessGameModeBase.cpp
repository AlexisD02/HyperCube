// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessGameModeBase.h"

void AEndlessGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Default"));

	// Start the timer for score increase
	GetWorldTimerManager().SetTimer(ScoreIncreaseTimerHandle, this, &AEndlessGameModeBase::IncreaseScore, ScoreIncreaseInterval, true);

	GetWorldTimerManager().SetTimer(PlaytimeUpdateTimerHandle, this, &AEndlessGameModeBase::UpdatePlaytime, TimerUpdate, true);
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

void AEndlessGameModeBase::IncreaseScore()
{
	score++; // Increase the score
}

FString AEndlessGameModeBase::GetScore()
{
    // Convert the score to a string
    FString ScoreString = FString::FromInt(score);

    // Calculate the number of zeros to prepend
    int32 ZerosToAdd = 5 - ScoreString.Len();

    // Prepend zeros to the score string
    FString FormattedScore = FString::Printf(TEXT("%0*d"), ZerosToAdd, 0) + ScoreString;

    return FormattedScore;
}

void AEndlessGameModeBase::UpdatePlaytime()
{
	Playtime += 1.0f;
}

FString AEndlessGameModeBase::GetPlaytime()
{
	// Calculate minutes and seconds
	int32 Minutes = FMath::FloorToInt(Playtime / 60.0f);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(Playtime, 60.0f));

	// Format playtime as MM:SS
	FString FormattedPlaytime = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

	return FormattedPlaytime;
}
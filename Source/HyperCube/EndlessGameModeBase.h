// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HYPERCUBE_API AEndlessGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void PointScored();

	UFUNCTION(BlueprintPure)
	int GetPointScored();

	UFUNCTION()
	void IncreaseScore();

	UFUNCTION(BlueprintPure)
	FString GetScore();

	UPROPERTY(EditAnywhere)
	int score = 0;

	UFUNCTION(BlueprintPure)
	FString GetPlaytime();

private:
	UPROPERTY()
	int pointsScored = 0;

	UPROPERTY(EditAnywhere)
	float ScoreIncreaseInterval = 0.1f; // Default score increase interval (1 second)

	// Timer handle for score increase
	FTimerHandle ScoreIncreaseTimerHandle;

	// Playtime variables
	UPROPERTY(EditAnywhere)
	float Playtime = 0.0f;

	FTimerHandle PlaytimeUpdateTimerHandle;

	UPROPERTY(EditAnywhere)
	float TimerUpdate = 1.0f;

	UFUNCTION()
	void UpdatePlaytime();
};
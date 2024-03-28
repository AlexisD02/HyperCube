// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HyperCubeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HYPERCUBE_API AHyperCubeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	UFUNCTION()
	void PointScored();

	UFUNCTION(BlueprintPure)
	int GetPointScored();

	UPROPERTY(EditAnywhere)
	int pointsScored = 0;

	UFUNCTION(BlueprintPure)
	FString GetPlaytime();

private:
	// Playtime variables
	UPROPERTY(EditAnywhere)
	float Playtime = 100.0f;

	UPROPERTY(EditAnywhere)
	float TimerUpdate = 1.0f;

	FTimerHandle PlaytimeUpdateTimerHandle;

	UFUNCTION()
	void UpdatePlaytime();
};

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

private:
	UPROPERTY()
	int pointsScored = 0;
};

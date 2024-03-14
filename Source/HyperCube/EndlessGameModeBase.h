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

private:
	UPROPERTY()
	int pointsScored = 0;
};
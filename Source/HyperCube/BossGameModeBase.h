// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BossGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HYPERCUBE_API ABossGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	// Health of cube
	UPROPERTY(EditAnywhere)
	int Health = 3;

public:
	void RemoveHealth(int amount);

	void AddHealth(int amount);

	int GetHealth();

	
};

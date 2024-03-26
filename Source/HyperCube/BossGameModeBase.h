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
	
public:
	ABossGameModeBase();

private:
	UPROPERTY(EditAnywhere)
	int MaxHealth = 3;

	// Health of cube
	UPROPERTY(EditAnywhere)
	int Health;
	
	UPROPERTY(EditAnywhere)
	int BossMaxHealth = 3;

	UPROPERTY(EditAnywhere)
	int BossHealth;

public:
	void RemoveHealth(int amount);

	void AddHealth(int amount);

	void RemoveBossHealth(int amount);

	UFUNCTION(BlueprintCallable)
	int GetMaxHealth();

	UFUNCTION(BlueprintCallable)
	int GetHealth();

	UFUNCTION(BlueprintCallable)
	int GetBossMaxHealth();

	UFUNCTION(BlueprintCallable)
	int GetBossHealth();
};

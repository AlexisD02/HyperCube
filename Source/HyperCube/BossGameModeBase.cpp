#include "BossGameModeBase.h"
#include "LaserEnemy.h"
// Fill out your copyright notice in the Description page of Project Settings.


ABossGameModeBase::ABossGameModeBase()
{
	Health = MaxHealth;
	BossHealth = BossMaxHealth;
}

void ABossGameModeBase::RemoveHealth(int amount)
{
	Health -= amount;
}

void ABossGameModeBase::AddHealth(int amount)
{
	Health += amount;
}

void ABossGameModeBase::RemoveBossHealth(int amount)
{
	BossHealth -= amount;
}

int ABossGameModeBase::GetMaxHealth()
{
	return MaxHealth;
}

int ABossGameModeBase::GetHealth()
{
	return Health;
}

int ABossGameModeBase::GetBossHealth()
{
	return BossHealth;
}

int ABossGameModeBase::GetBossMaxHealth()
{
	return BossMaxHealth;
}
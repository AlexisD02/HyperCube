// Fill out your copyright notice in the Description page of Project Settings.


#include "BossGameModeBase.h"

void ABossGameModeBase::RemoveHealth(int amount)
{
	Health -= amount;
}

void ABossGameModeBase::AddHealth(int amount)
{
	Health += amount;
}

int ABossGameModeBase::GetHealth()
{
	return Health;
}

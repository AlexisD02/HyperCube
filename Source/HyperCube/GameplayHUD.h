// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HYPERCUBE_API GameplayHUD
{
public:

	void BeginPlay();

private:

	// a function that return the point that the player has gathered
	UFUNCTION()
	int GetPoints();

	// the widget that gathers the point and shows them
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> GameplayHUDClass;
	UPROPERTY(EditAnywhere)
	int NumberOfPpoints;
	UPROPERTY()
	UUserWidget* PointCount;
};

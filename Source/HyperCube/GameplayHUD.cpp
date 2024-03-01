// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayHUD.h"
#include "Blueprint/UserWidget.h"


void GameplayHUD::BeginPlay()
{

	NumberOfPpoints = 0;
	PointCount = CreateWidget(this, GameplayHUDClass);
	if (PointCount != nullptr) {
		PointCount->AddToViewport();
	}
}

int GameplayHUD::GetPoints()
{
	return NumberOfPpoints;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultLevelGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class HYPERCUBE_API ADefaultLevelGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanDoubleJump = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanDash = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCanGroundSlam = false;
};

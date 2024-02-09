// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerGiver.generated.h"

UCLASS()
class HYPERCUBE_API APowerGiver : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerGiver();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//**** 
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* PowerGiverMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bGiveDoubleJump = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bGiveDash = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bGiveGroundSlam = false;
	//****
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};

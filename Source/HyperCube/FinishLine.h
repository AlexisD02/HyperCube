// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubePawn.h"
#include "CustomPlayerController.h"
#include "FinishLine.generated.h"

UCLASS()
class HYPERCUBE_API AFinishLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinishLine();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Collision box to detect overlaps with the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* CollisionBox;

	// Overlap begin function
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Timer for delayed actions
	FTimerHandle DelayTimer;

	// Function to detach camera from cube and display widget after a delay
	void TriggerAction();

	ACubePawn* CubePawn;
};

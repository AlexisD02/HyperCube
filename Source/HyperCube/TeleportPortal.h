// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubePawn.h"
#include "TeleportPortal.generated.h"

UCLASS()
class HYPERCUBE_API ATeleportPortal : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATeleportPortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PortalMesh;

	// Collision box to detect overlaps with the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* PortalCollision;

	// Overlap begin function
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	ACubePawn* CubePawn;

	FVector DestinationPoint;
};

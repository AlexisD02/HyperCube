// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CubePawn.h"
#include "CustomCubeMovementComponent.h"
#include "GroundSlamAP.generated.h"

UCLASS()
class HYPERCUBE_API AGroundSlamAP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroundSlamAP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Main mesh for the ammo box
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* GroundSlamArrowMesh;

	// Collision box to detect overlaps with the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* CollisionBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	ACubePawn* CubePawn;

private:
	// Speed of rotation (degrees per second)
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 90.0f;

	// Speed of vertical movement
	UPROPERTY(EditAnywhere)
	float FloatSpeed = 20.0f;

	// Current time since the game started
	float RunningTime = 0.0f;

};

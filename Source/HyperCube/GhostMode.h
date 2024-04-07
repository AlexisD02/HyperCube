// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubePawn.h"
#include "GhostMode.generated.h"

UCLASS()
class HYPERCUBE_API AGhostMode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGhostMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GhostMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY()
	ACubePawn* CubePawn;


private:

	UPROPERTY()
	class AHyperCubeGameModeBase* GameModeRef;

	// Speed of rotation (degrees per second)
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 90.0f;

	UPROPERTY(EditAnywhere)
	float FloatSpeed = 20.0f;

	// Current time since the game started
	float RunningTime = 0.0f;

};

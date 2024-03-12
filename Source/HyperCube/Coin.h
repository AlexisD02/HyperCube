// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CubePawn.h"
#include "Coin.generated.h"

UCLASS()
class HYPERCUBE_API ACoin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CoinMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collisionbox;

	UPROPERTY()
	ACubePawn* CubePawn;


private:

	UPROPERTY()
	class ADefaultLevelGameModeBase* GameModeRef;



	UPROPERTY(EditAnywhere)
	float FloatSpeed = 20.0f;

	// Current time since the game started
	float RunningTime = 0.0f;
};

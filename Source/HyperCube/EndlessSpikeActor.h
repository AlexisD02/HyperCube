// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndlessSpikeActor.generated.h"

UCLASS()
class HYPERCUBE_API AEndlessSpikeActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEndlessSpikeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SpikeMesh;

	// Function to handle when this actor hits another
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};


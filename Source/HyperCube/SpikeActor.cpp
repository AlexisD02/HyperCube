// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeActor.h"
#include "Kismet/GameplayStatics.h"
#include "CubePawn.h"
#include "CustomPlayerController.h"

// Sets default values
ASpikeActor::ASpikeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spike Mesh"));
	SetRootComponent(SpikeMesh);

}

// Called when the game starts or when spawned
void ASpikeActor::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ASpikeActor::OnHit);
}

// Called every frame
void ASpikeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpikeActor::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Spike Collided with Something."));

	if (OtherActor->GetClass()->IsChildOf(ACubePawn::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Spike Collided with Cuber!"));

		// Attempt to cast to CustomPlayerController
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (ACustomPlayerController* CustomController = Cast<ACustomPlayerController>(PlayerController))
		{
			// Call GameOverScreen function if accessible
			CustomController->GameOverScreen();
		}
		OtherActor->Destroy();  // Remove teabag so ApplyDamage function does not run multiple times 
	}
}
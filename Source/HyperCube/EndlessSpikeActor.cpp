// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessSpikeActor.h"
#include "Kismet/GameplayStatics.h"
#include "EndlessCubePawn.h"
#include "EndlessPlayerController.h"

// Sets default values
AEndlessSpikeActor::AEndlessSpikeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spike Mesh"));
	SetRootComponent(SpikeMesh);

}

// Called when the game starts or when spawned
void AEndlessSpikeActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &AEndlessSpikeActor::OnHit);
}

// Called every frame
void AEndlessSpikeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function to handle when this actor hits another
void AEndlessSpikeActor::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Spike Collided with Something."));
	// Check if the OtherActor is of type AEndlessCubePawn
	if (AEndlessCubePawn* EndlessCubePawn = Cast<AEndlessCubePawn>(OtherActor)) {
		// Destroy the pawn
		EndlessCubePawn->Destroy();
		// Attempt to cast to CustomPlayerController
		// Get a reference to the player controller
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController) {
			// Check if the player controller is of type AEndlessPlayerController
			AEndlessPlayerController* EndlessPlayerController = Cast<AEndlessPlayerController>(PlayerController);
			if (EndlessPlayerController) {
				// Call a function on the player controller
				EndlessPlayerController->GameOverScreen();
			}
		}
	}
}


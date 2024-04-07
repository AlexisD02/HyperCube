// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostMode.h"
#include "CubePawn.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "CustomCubeMovementComponent.h"

// Sets default values
AGhostMode::AGhostMode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	GhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ghost"));
	GhostMesh->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionBox->SetupAttachment(GhostMesh);
	CollisionBox->SetBoxExtent(FVector(40.0f, 70.0f, 10.0f));
	CollisionBox->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void AGhostMode::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AGhostMode::OnOverlapBegin);
	
}

// Called every frame
void AGhostMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate the actor
	AddActorLocalRotation(FRotator(0.f, RotationSpeed * DeltaTime, 0.f));

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed; // FloatSpeed controls the speed of the floating
	SetActorLocation(NewLocation);

	RunningTime += DeltaTime; // Update running time

}

void AGhostMode::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	CubePawn = Cast<ACubePawn>(OtherActor);

	if (CubePawn) {
		CubePawn->CubeMovement->EnableGhost();
		Destroy();

	}
}


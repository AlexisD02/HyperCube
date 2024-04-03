// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrinkAP.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShrinkAP::AShrinkAP()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create subobjects for the different components.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    ShrinkMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShrinkMesh"));
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

    // Set default values for the components.
    ShrinkMesh->SetupAttachment(RootComponent);
    CollisionBox->SetupAttachment(ShrinkMesh);
    CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 150.0f));
    CollisionBox->SetCollisionProfileName(TEXT("Trigger"));

}

// Called when the game starts or when spawned
void AShrinkAP::BeginPlay()
{
	Super::BeginPlay();

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AShrinkAP::OnOverlapBegin);

}

// Called every frame
void AShrinkAP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Float the actor up and down
    FVector NewLocation = GetActorLocation();
    float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
    NewLocation.Z += DeltaHeight * FloatSpeed; // FloatSpeed controls the speed of the floating
    SetActorLocation(NewLocation);

    RunningTime += DeltaTime; // Update running time

}

void AShrinkAP::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CubePawn = Cast<ACubePawn>(OtherActor);

    if (CubePawn) {
        CubePawn->CubeMovement->EnableShrink();
        Destroy();
    }
}
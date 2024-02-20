// Fill out your copyright notice in the Description page of Project Settings.


#include "DoubleJumpAP.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoubleJumpAP::ADoubleJumpAP()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create subobjects for the different components.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    DoubleJumpABoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoubleJumpABoxMesh"));
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

    // Set default values for the components.
    DoubleJumpABoxMesh->SetupAttachment(RootComponent);
    CollisionBox->SetupAttachment(DoubleJumpABoxMesh);
    CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 150.0f)); // Adjust the size as needed
    CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ADoubleJumpAP::BeginPlay()
{
    Super::BeginPlay();

    // Register Events
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADoubleJumpAP::OnOverlapBegin);
}

// Called every frame
void ADoubleJumpAP::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime); // Call parent class tick function

    // Float the actor up and down
    FVector NewLocation = GetActorLocation();
    float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
    NewLocation.Z += DeltaHeight * FloatSpeed; // FloatSpeed controls the speed of the floating
    SetActorLocation(NewLocation);

    RunningTime += DeltaTime; // Update running time
}

void ADoubleJumpAP::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CubePawn = Cast<ACubePawn>(OtherActor);

    if (CubePawn) {
        CubePawn->CubeMovement->EnableDoubleJump();
        Destroy();
    }
}


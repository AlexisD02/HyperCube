// Fill out your copyright notice in the Description page of Project Settings.


#include "DashAP.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADashAP::ADashAP()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create subobjects for the different components.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    DashArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DashArrowMesh"));
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));

    // Set default values for the components.
    DashArrowMesh->SetupAttachment(RootComponent);
    CollisionBox->SetupAttachment(DashArrowMesh);
    CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 150.0f));
    CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ADashAP::BeginPlay()
{
    Super::BeginPlay();

    // Register Events
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADashAP::OnOverlapBegin);
}

// Called every frame
void ADashAP::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime); // Call parent class tick function

    // Float the actor up and down
    FVector NewLocation = GetActorLocation();
    float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
    NewLocation.Z += DeltaHeight * FloatSpeed; // FloatSpeed controls the speed of the floating
    SetActorLocation(NewLocation);

    RunningTime += DeltaTime; // Update running time
}

void ADashAP::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CubePawn = Cast<ACubePawn>(OtherActor);

    if (CubePawn) {
        CubePawn->CubeMovement->EnableDash();
        Destroy();
    }
}

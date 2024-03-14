// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportPortal.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATeleportPortal::ATeleportPortal()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
    PortalMesh->SetupAttachment(RootComponent);

    // Create subobjects for the different components.
    PortalCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalCollision"));
    PortalCollision->SetBoxExtent(FVector(150.0f, 10.0f, 300.0f));
    PortalCollision->SetCollisionProfileName(TEXT("Trigger"));
    PortalCollision->SetupAttachment(PortalMesh);
}

// Called when the game starts or when spawned
void ATeleportPortal::BeginPlay()
{
    Super::BeginPlay();

    // Register Events
    PortalCollision->OnComponentBeginOverlap.AddDynamic(this, &ATeleportPortal::OnOverlapBegin);

    // Set up destination point (adjust this based on your game's requirements)
    DestinationPoint = FVector(1000.f, 0.f, 500.f);
}

void ATeleportPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CubePawn = Cast<ACubePawn>(OtherActor);
    // Check if the portal is linked to another portal
    if (CubePawn) {
        // Teleport the overlapping actor to the linked portal's destination point
        CubePawn->SetActorLocation(DestinationPoint);
    }
}

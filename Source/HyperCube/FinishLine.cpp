// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishLine.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFinishLine::AFinishLine()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create subobjects for the different components.
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetBoxExtent(FVector(150.0f, 10.0f, 300.0f));
    CollisionBox->SetCollisionProfileName(TEXT("Trigger"));
    RootComponent = CollisionBox;
}

// Called when the game starts or when spawned
void AFinishLine::BeginPlay()
{
    Super::BeginPlay();

    // Register Events
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFinishLine::OnOverlapBegin);
}

void AFinishLine::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CubePawn = Cast<ACubePawn>(OtherActor);

    if (CubePawn) {
        CubePawn->DetachCamera();
        // Trigger action after a delay
        GetWorld()->GetTimerManager().SetTimer(DelayTimer, this, &AFinishLine::TriggerAction, 2.0f, false);
    }
}

// Function to detach camera from cube and display widget after a delay
void AFinishLine::TriggerAction()
{
    // Attempt to cast to CustomPlayerController
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (ACustomPlayerController* CustomController = Cast<ACustomPlayerController>(PlayerController))
    {
        // Call WinScreen function if accessible
        CustomController->WinScreen();
    }
}
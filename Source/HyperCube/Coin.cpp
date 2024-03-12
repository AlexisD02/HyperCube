// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "CubePawn.h"
#include "DefaultLevelGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ACoin::ACoin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin"));
	CoinMesh->SetupAttachment(RootComponent);

	Collisionbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collisionbox->SetupAttachment(CoinMesh);
	Collisionbox->SetBoxExtent(FVector(40.0f, 70.0f, 10.0f));
	Collisionbox->SetCollisionProfileName("Trigger");



}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	Collisionbox->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);
	GameModeRef = Cast<ADefaultLevelGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed; // FloatSpeed controls the speed of the floating
	SetActorLocation(NewLocation);

	RunningTime += DeltaTime; // Update running time
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("coin over"));
	CubePawn = Cast<ACubePawn>(OtherActor);
	if (CubePawn) {

		if (GameModeRef)
		{
			GameModeRef->PointScored();
			Destroy();
		}

	}

}


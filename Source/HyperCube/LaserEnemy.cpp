// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserEnemy.h"
#include "CollisionQueryParams.h"
#include "Kismet/GameplayStatics.h"
#include "CubePawn.h"
#include "CustomPlayerController.h"

// Sets default values
ALaserEnemy::ALaserEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaserEnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserEnemyMesh"));
	LaserEnemyMesh->SetSimulatePhysics(true);
	RootComponent = LaserEnemyMesh;

	TakeDamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TakeDamageBox"));
	TakeDamageBox->SetupAttachment(LaserEnemyMesh);
	//TakeDamageBox->SetBoxExtent(FVector(100.0f, 100.0f, 150.0f));
	TakeDamageBox->SetCollisionProfileName(TEXT("Trigger"));

	DealDamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DealDamageBox"));
	DealDamageBox->SetupAttachment(LaserEnemyMesh);
	//TakeDamageBox->SetBoxExtent(FVector(100.0f, 100.0f, 150.0f));
	DealDamageBox->SetCollisionProfileName(TEXT("Trigger"));
}

// Called when the game starts or when spawned
void ALaserEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// Register Events
	DealDamageBox->OnComponentBeginOverlap.AddDynamic(this, &ALaserEnemy::DealDamageToPlayerEvent);
	TakeDamageBox->OnComponentBeginOverlap.AddDynamic(this, &ALaserEnemy::TakeDamageEvent);
}

// Called every frame
void ALaserEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldFire) if (bCanFire) LaserFire();
	if (bCanPatrol) if (bShouldInitiatePatrol) InitiatePatrol();
	if (!bShouldInitiatePatrol) Patrol(DeltaTime);
}

void ALaserEnemy::LaserFire()
{
	// Attempt to cast to CustomPlayerController
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	FVector Start = GetActorLocation();

	FVector End;
	if (bShouldFireAtPlayer) if (PlayerController) if (auto const Player = PlayerController->GetPawn()) End = Start - Player->GetActorLocation();
	else End = Start - FVector(0.0f, -LaserDistance, 0.0f);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, true, 0.1f, 0.0f, 35.0f);
	CollisionParams.AddIgnoredActor(GetOwner()); // Ignore the cube itself

	// Perform the raycast
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

	// Log the result
	UE_LOG(LogTemp, Warning, TEXT("Laser has hit: %s"), bHit ? TEXT("True") : TEXT("False"));

	if (bHit)  // The enemy hit something
	{
		if (HitResult.GetActor())  // The target the enemy hit is not null
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Something: %f"), *HitResult.GetActor()->GetName());

			if (HitResult.GetActor()->GetClass()->IsChildOf(ACubePawn::StaticClass()))  // If the target was the player
			{
				if (ACustomPlayerController* CustomController = Cast<ACustomPlayerController>(PlayerController))
				{
					// Call GameOverScreen function if accessible
					CustomController->GameOverScreen();
					HitResult.GetActor()->Destroy();
				}
			}
		}
	}

	GetWorld()->GetTimerManager().SetTimer(LaserTimer, this, &ALaserEnemy::EnableFire, RPM, false);
	bCanFire = false;
}

void ALaserEnemy::EnableFire()
{
	bCanFire = true;
}

void ALaserEnemy::InitiatePatrol()
{
	bShouldInitiatePatrol = false;
	MovementSpeed *= -1;
	GetWorld()->GetTimerManager().SetTimer(PatrolTimer, this, &ALaserEnemy::EnablePatrol, PatrolDuration, false);
}

void ALaserEnemy::EnablePatrol()
{
	bShouldInitiatePatrol = true;
}

void ALaserEnemy::Patrol(float DeltaTime)
{
	// Handle continuous movement based on the current speed
	FVector NewLocation = GetActorLocation() + FVector(0.0f, MovementSpeed * DeltaTime, 0.0f);
	SetActorLocation(NewLocation);
}

float ALaserEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy took some damage!!!"));

	Health -= DamageAmount;

	return DamageAmount;
}

// Functions to run when the corisponding collision boxes overlap with the player
void ALaserEnemy::DealDamageToPlayerEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (auto* const Player = PlayerController->GetPawn())
		{
			if (UStaticMeshComponent* CubeMesh = Cast<UStaticMeshComponent>(Player->GetRootComponent()))
			{
				CubeMesh->SetPhysicsLinearVelocity(FVector(1000.0f, 1000.0f, 1000.0f));

				UE_LOG(LogTemp, Warning, TEXT("Enemy colided with player (Deal damage)!!!"));
			}
		}
	}
}

void ALaserEnemy::TakeDamageEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Health--;

	if (Health < 0) Destroy();
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserEnemy.h"
#include "CollisionQueryParams.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "CubePawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "CustomPlayerController.h"
#include "BossGameModeBase.h"

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

	DealDamageBoxLeft = CreateDefaultSubobject<UBoxComponent>(TEXT("DealDamageBoxLeft"));
	DealDamageBoxLeft->SetupAttachment(LaserEnemyMesh);
	DealDamageBoxLeft->SetCollisionProfileName(TEXT("Trigger"));

	DealDamageBoxRight = CreateDefaultSubobject<UBoxComponent>(TEXT("DealDamageBoxRight"));
	DealDamageBoxRight->SetupAttachment(LaserEnemyMesh);
	DealDamageBoxRight->SetCollisionProfileName(TEXT("Trigger"));

	LaserLineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserLineMesh"));
	LaserLineMesh->SetupAttachment(LaserEnemyMesh);
	LaserLineMesh->SetVisibility(false); // Initially invisible
	LaserLineMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ALaserEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Get a reference to the boss gamemode base
	GameModeRef = Cast<ABossGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	// Register Events
	DealDamageBoxLeft->OnComponentBeginOverlap.AddDynamic(this, &ALaserEnemy::DealDamageToPlayerEventLeft);
	DealDamageBoxRight->OnComponentBeginOverlap.AddDynamic(this, &ALaserEnemy::DealDamageToPlayerEventRight);
	TakeDamageBox->OnComponentBeginOverlap.AddDynamic(this, &ALaserEnemy::TakeDamageEvent);

	GetWorld()->GetTimerManager().SetTimer(LaserTimer, this, &ALaserEnemy::LaserFire, RPM, true);
}

// Called every frame
void ALaserEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (bShouldFire) if (bCanFire) LaserFire();

	if (bCanPatrol) if (bShouldInitiatePatrol) InitiatePatrol();
	if (!bShouldInitiatePatrol) Patrol(DeltaTime);
}

void ALaserEnemy::LaserFire()
{
	// Calculate the start and end locations for the line trace
	FVector Start = GetActorLocation();
	if (!GetWorld()->GetFirstPlayerController()->GetPawn()) return; // Ensure there's a player pawn
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(); // Get player's location
	FVector DirectionToPlayer = (PlayerLocation - Start).GetSafeNormal(); // Direction vector from enemy to player
	FVector End = Start + (DirectionToPlayer * 1000.0f);

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignore the shooter

	LaserLineMesh->SetWorldLocation(Start);
	LaserLineMesh->SetWorldRotation(DirectionToPlayer.Rotation() + FRotator(-90.0f, 0.0f, 0.0f));
	LaserLineMesh->SetVisibility(true);

	GetWorld()->GetTimerManager().SetTimer(LaserLineTimer, this, &ALaserEnemy::RemoveLaser, laserDuration, false);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor) {
			// Cast the hit actor to CubePawn
			ACubePawn* HitPawn = Cast<ACubePawn>(HitActor);
			if (HitPawn) { // If the cast is successful, it means the hit actor is a CubePawn
				if (GameModeRef)
				{
					GameModeRef->RemoveHealth(1);

					if (GameModeRef->GetHealth() <= 0)
					{
						HitPawn->Destroy();

						APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
						if (ACustomPlayerController* CustomController = Cast<ACustomPlayerController>(PlayerController)) {
							// Call WinScreen function if accessible
							CustomController->GameOverScreen();
						}
					}
				}
			}
		}
	}
}

void ALaserEnemy::RemoveLaser()
{
	LaserLineMesh->SetVisibility(false);
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
void ALaserEnemy::DealDamageToPlayerEventLeft(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (auto* const Player = PlayerController->GetPawn())
		{
			if (UStaticMeshComponent* CubeMesh = Cast<UStaticMeshComponent>(Player->GetRootComponent()))
			{
				CubeMesh->SetPhysicsLinearVelocity(FVector(0.0f, -3000.0f, 0.0f));

				UE_LOG(LogTemp, Warning, TEXT("Enemy colided with player (Deal damage)!!!"));

				if (GameModeRef)
				{
					GameModeRef->RemoveHealth(1);

					if (GameModeRef->GetHealth() <= 0)
					{
						Player->Destroy();

						//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
						if (ACustomPlayerController* CustomController = Cast<ACustomPlayerController>(PlayerController)) {
							// Call WinScreen function if accessible
							CustomController->GameOverScreen();
						}
					}
				}
			}
		}
	}
}

// Functions to run when the corisponding collision boxes overlap with the player
void ALaserEnemy::DealDamageToPlayerEventRight(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (auto* const Player = PlayerController->GetPawn())
		{
			if (UStaticMeshComponent* CubeMesh = Cast<UStaticMeshComponent>(Player->GetRootComponent()))
			{
				CubeMesh->SetPhysicsLinearVelocity(FVector(0.0f, 3000.0f, 0.0f));

				UE_LOG(LogTemp, Warning, TEXT("Enemy colided with player (Deal damage)!!!"));

				if (GameModeRef)
				{
					GameModeRef->RemoveHealth(1);

					if (GameModeRef->GetHealth() <= 0)
					{
						Player->Destroy();

						//APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
						if (ACustomPlayerController* CustomController = Cast<ACustomPlayerController>(PlayerController)) {
							// Call WinScreen function if accessible
							CustomController->GameOverScreen();
						}
					}
				}
			}
		}
	}
}

void ALaserEnemy::TakeDamageEvent(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Health--;

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (auto* const Player = PlayerController->GetPawn())
		{
			if (UStaticMeshComponent* CubeMesh = Cast<UStaticMeshComponent>(Player->GetRootComponent()))
			{
				CubeMesh->SetPhysicsLinearVelocity(FVector(0.0f, 0.0f, 2000.0f));

				UE_LOG(LogTemp, Warning, TEXT("Bounce PLAYER!!!"));
			}
		}
	}

	if (Health <= 0) Destroy();
}

// Value that appears on screen for Health
int ALaserEnemy::GetHealth()
{
	return Health;
}
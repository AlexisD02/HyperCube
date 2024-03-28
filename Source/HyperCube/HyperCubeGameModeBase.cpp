// Copyright Epic Games, Inc. All Rights Reserved.


#include "HyperCubeGameModeBase.h"
#include "CustomPlayerController.h"

void AHyperCubeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Default"));

	GetWorldTimerManager().SetTimer(PlaytimeUpdateTimerHandle, this, &AHyperCubeGameModeBase::UpdatePlaytime, TimerUpdate, true);
}

void AHyperCubeGameModeBase::PointScored()
{
	pointsScored++;
	UE_LOG(LogTemp, Warning, TEXT("Points: %f"), pointsScored);
}

int AHyperCubeGameModeBase::GetPointScored()
{
	return pointsScored;
}

void AHyperCubeGameModeBase::UpdatePlaytime()
{
    Playtime -= 1.0f;

    if (Playtime <= 0.0f) {
        // Playtime has run out - call the relevant function on the PlayerController.
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController) {
            // Replace 'YourPlayerControllerClass' with your actual player controller class name
            // and 'YourFunctionToCall' with the function you want to call on the player controller.
            ACustomPlayerController* MyController = Cast<ACustomPlayerController>(PlayerController);
            if (MyController) {
                MyController->GameOverScreen();
            }
        }
    }
}


FString AHyperCubeGameModeBase::GetPlaytime()
{
	// Calculate minutes and seconds
	int32 Minutes = FMath::FloorToInt(Playtime / 60.0f);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(Playtime, 60.0f));

	// Format playtime as MM:SS
	FString FormattedPlaytime = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

	return FormattedPlaytime;
}
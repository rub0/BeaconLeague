// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaconLeague.h"
#include "BeaconLeagueGameMode.h"

#include "BLCameraSpectatorPawn.h"
#include "BeaconController.h"
#include "Ball.h"
#include "Beacon.h"

ABeaconLeagueGameMode::ABeaconLeagueGameMode()
{
	PlayerControllerClass = ABeaconController::StaticClass();
	DefaultPawnClass = ABLCameraSpectatorPawn::StaticClass();
	World = GetWorld();

}

void ABeaconLeagueGameMode::SpawnBeacon(const FVector &position)
{
	FVector respos = (position + FVector(0, 0, 5.0f));

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("StartTCPReceiver>> Listen socket could not be created! ~> %s"), &BeaconClass));
	AActor* res = World->SpawnActor(BeaconClass, &respos);

	if (!res)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("beacon class not found")));
	}
}

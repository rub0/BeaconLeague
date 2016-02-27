// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaconLeague.h"
#include "BeaconLeagueGameMode.h"

#include "BLCameraSpectatorPawn.h"
#include "BeaconController.h"

ABeaconLeagueGameMode::ABeaconLeagueGameMode()
{
	PlayerControllerClass = ABeaconController::StaticClass();
	DefaultPawnClass = ABLCameraSpectatorPawn::StaticClass();
}



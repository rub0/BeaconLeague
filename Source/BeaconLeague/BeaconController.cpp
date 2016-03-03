// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaconLeague.h"
#include "BeaconController.h"

/**
* 
*/
ABeaconController::ABeaconController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

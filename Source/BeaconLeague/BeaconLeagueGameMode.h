// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "BeaconLeagueGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BEACONLEAGUE_API ABeaconLeagueGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABeaconLeagueGameMode();
	
	static const uint16 MAX_BEACONS = 3;

	void SpawnBeacon(const FVector &position);


	/** The class of PlayerController to spawn for players logging in. */
	UPROPERTY(EditAnywhere, noclear, BlueprintReadOnly, Category=Classes)
	TSubclassOf<class ABall> BallClass;

	UPROPERTY(EditAnywhere, noclear, BlueprintReadOnly, Category=Classes)
	TSubclassOf<class ABeacon> BeaconClass;

private:
	UWorld* World;
	TArray<AActor*> BeaconsSpawned;
	uint16 NnewBeacon;
};

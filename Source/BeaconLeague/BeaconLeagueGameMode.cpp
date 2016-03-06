// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaconLeague.h"
#include "BeaconLeagueGameMode.h"

#include "BLCameraSpectatorPawn.h"
#include "BeaconController.h"
#include "Ball.h"
#include "Beacon.h"

ABeaconLeagueGameMode::ABeaconLeagueGameMode(): NnewBeacon(0)
{
	PlayerControllerClass = ABeaconController::StaticClass();
	DefaultPawnClass = ABLCameraSpectatorPawn::StaticClass();
	World = GetWorld();
}

void ABeaconLeagueGameMode::SpawnBeacon(const FVector &position)
{
	FVector respos = (position + FVector(0, 0, 20.0f));

	TArray<FOverlapResult> overlapResult;

	FCollisionQueryParams oParams(false);
	oParams.AddIgnoredActor(this);

	FCollisionResponseParams ResponseParam(ECollisionResponse::ECR_Block);

	World->OverlapMulti(overlapResult, respos, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(50), oParams);

	if (overlapResult.Num() > 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("no puedes spawnear el beacon ahi! %d "), overlapResult.Num()));
	}
	else if (BeaconsSpawned.Num() == MAX_BEACONS)
	{
		BeaconsSpawned[NnewBeacon]->SetActorLocation(respos);
		NnewBeacon = (NnewBeacon + 1) % MAX_BEACONS;
	}
	else
	{
		AActor* newBeacon = World->SpawnActor(BeaconClass, &respos);

		if (newBeacon)
		{
			BeaconsSpawned.Add(newBeacon);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("you cannot spawn a beacon there!")));
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaconLeague.h"
#include "Beacon.h"


// Sets default values
ABeacon::ABeacon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ABeacon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABeacon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ABeacon::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


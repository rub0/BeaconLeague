// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaconLeague.h"
#include "BLCameraSpectatorPawn.h"

ABLCameraSpectatorPawn::ABLCameraSpectatorPawn(const FObjectInitializer& ObjectInitializer)
{
    // enable Tick function
    PrimaryActorTick.bCanEverTick = true;

    // disable standard WASD movement
    bAddDefaultMovementBindings = false;

    // not needed Pitch Yaw Roll
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;        
    bUseControllerRotationRoll = false;

    // set defaults
    CameraRadius = 200.0f;
    CameraRadiusMin = 200.0f;                // min height
    CameraRadiusMax = 200.0f;                // max height
    
    CameraZAnlge = 0.0;                        // yaw
    
    CameraHeightAngle = 90.0f;                // pitch
    CameraHeightAngleMin = 90.0f;
    CameraHeightAngleMax = 90.0f;

    CameraZoomSpeed = 200.0f;                // wheel
    CameraRotationSpeed = 10.0f;            // wheel + ctrl
    CameraMovementSpeed = 3000.0f;            // in all directions
    
    CameraScrollBoundary = 25.0f;            // screen edge width
    
    bCanMoveCamera = true;

    // intialize the camera
    CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("RTS Camera"));
	SpringArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("Spring Arm"));
    CameraComponent->AttachParent = SpringArm;
    //CameraComponent->bUsePawnControlRotation = false;
    RepositionCamera();
}


//////////////////////////////////////////////////////////////////


void ABLCameraSpectatorPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    check(InputComponent);

    Super::SetupPlayerInputComponent(InputComponent);

    // mouse zoom
    InputComponent->BindAction("ZoomOutByWheel", IE_Pressed, this, &ABLCameraSpectatorPawn::ZoomOutByWheel);
    InputComponent->BindAction("ZoomInByWheel", IE_Pressed, this, &ABLCameraSpectatorPawn::ZoomInByWheel);
    
    // mouse rotate (+Ctrl or +Alt)
    InputComponent->BindAction("RotateLeftByWheel", IE_Pressed, this, &ABLCameraSpectatorPawn::RotateLeftByWheel);
    InputComponent->BindAction("RotateRightByWheel", IE_Pressed, this, &ABLCameraSpectatorPawn::RotateRightByWheel);
    InputComponent->BindAction("RotateUpByWheel", IE_Pressed, this, &ABLCameraSpectatorPawn::RotateUpByWheel);
    InputComponent->BindAction("RotateDownByWheel", IE_Pressed, this, &ABLCameraSpectatorPawn::RotateDownByWheel);

    // keyboard move (WASD, Home/End)
    InputComponent->BindAxis("MoveForward", this, &ABLCameraSpectatorPawn::MoveCameraForwardInput);
    InputComponent->BindAxis("MoveRight", this, &ABLCameraSpectatorPawn::MoveCameraRightInput);
    InputComponent->BindAxis("MoveUp", this, &ABLCameraSpectatorPawn::MoveCameraUpInput);
    InputComponent->BindAxis("ZoomIn", this, &ABLCameraSpectatorPawn::ZoomCameraInInput);

    // double speed (WASD +Shift)
    InputComponent->BindAxis("FastMove", this, &ABLCameraSpectatorPawn::FastMoveInput);
    // yaw and pitch (WASD +Ctrl)
    InputComponent->BindAxis("Rotate", this, &ABLCameraSpectatorPawn::RotateInput);
}


//////////////////////////////////////////////////////////////////


void ABLCameraSpectatorPawn::ZoomInByWheel()
{
    if (!bCanMoveCamera)    return;

    CameraRadius -= CameraZoomSpeed * FastMoveValue;
    CameraRadius = FMath::Clamp(CameraRadius, CameraRadiusMin, CameraRadiusMax);

    RepositionCamera();
}


void ABLCameraSpectatorPawn::ZoomOutByWheel()
{
    if (!bCanMoveCamera)    return;

    CameraRadius += CameraZoomSpeed * FastMoveValue;
    CameraRadius = FMath::Clamp(CameraRadius, CameraRadiusMin, CameraRadiusMax);

    RepositionCamera();
}


void ABLCameraSpectatorPawn::RotateLeftByWheel()
{
    if (!bCanMoveCamera)    return;

    CameraZAnlge -= CameraRotationSpeed * FastMoveValue;

    RepositionCamera();
}


void ABLCameraSpectatorPawn::RotateRightByWheel()
{
    if (!bCanMoveCamera)    return;

    CameraZAnlge += CameraRotationSpeed * FastMoveValue;

    RepositionCamera();
}


void ABLCameraSpectatorPawn::RotateUpByWheel()
{
    if (!bCanMoveCamera)    return;

    CameraHeightAngle += CameraRotationSpeed * FastMoveValue;
    CameraHeightAngle = FMath::Clamp(CameraHeightAngle, CameraHeightAngleMin, CameraHeightAngleMax);

    RepositionCamera();
}


void ABLCameraSpectatorPawn::RotateDownByWheel()
{
    if (!bCanMoveCamera)    return;

    CameraHeightAngle -= CameraRotationSpeed * FastMoveValue;
    CameraHeightAngle = FMath::Clamp(CameraHeightAngle, CameraHeightAngleMin, CameraHeightAngleMax);

    RepositionCamera();
}

//---------------

void ABLCameraSpectatorPawn::RepositionCamera()
{
    FVector newLocation(0.0f, 0.0f, 0.0f);
    FRotator newRotation(0.0f, 0.0f, 0.0f);

    float sinCameraZAngle = FMath::Sin(FMath::DegreesToRadians(CameraZAnlge));
    float cosCameraZAngle = FMath::Cos(FMath::DegreesToRadians(CameraZAnlge));

    float sinCameraHeightAngle = FMath::Sin(FMath::DegreesToRadians(CameraHeightAngle));
    float cosCameraHeightAngle = FMath::Cos(FMath::DegreesToRadians(CameraHeightAngle));

    newLocation.X = cosCameraZAngle * cosCameraHeightAngle * CameraRadius;
    newLocation.Y = sinCameraZAngle * cosCameraHeightAngle * CameraRadius;
    newLocation.Z = sinCameraHeightAngle * CameraRadius;

    newRotation = (FVector(0.0f, 0.0f, 0.0f) - newLocation).Rotation();

    // new camera location and rotation
    CameraComponent->SetRelativeRotation(newRotation);
	SetActorLocation(bCameraPosition);
}


//////////////////////////////////////////////////////////////////


void ABLCameraSpectatorPawn::FastMoveInput(float Direction)
{
    if (!bCanMoveCamera)    return;

    // left or right does not matter, to set double speed in any direction
    FastMoveValue = FMath::Abs(Direction) * 2.0f;

    // used as multiplier so must be 1 if not pressed
    if (FastMoveValue == 0.0f)
    {
        FastMoveValue = 1.0f;
    }
}


void ABLCameraSpectatorPawn::RotateInput(float Direction)
{
    if (!bCanMoveCamera)    return;

    // left or right does not matter
    RotateValue = FMath::Abs(Direction);
}


void ABLCameraSpectatorPawn::MoveCameraForwardInput(float Direction)
{
    if (!bCanMoveCamera)    return;

    MoveForwardValue = Direction;
}


void ABLCameraSpectatorPawn::MoveCameraRightInput(float Direction)
{
    if (!bCanMoveCamera)    return;

    MoveRightValue = Direction;
}


void ABLCameraSpectatorPawn::MoveCameraUpInput(float Direction)
{
    if (!bCanMoveCamera)    return;

    MoveUpValue = Direction;
}


void ABLCameraSpectatorPawn::ZoomCameraInInput(float Direction)
{
    if (!bCanMoveCamera)    return;

    ZoomInValue = Direction;
}


//------------------------------------------------------------


void ABLCameraSpectatorPawn::MoveCameraForward(float Direction)
{
    float MovementValue = Direction * CameraMovementSpeed;
    FVector DeltaMovement = MovementValue * GetIsolatedCameraYaw().Vector();
    FVector NewLocation = GetActorLocation() + DeltaMovement;

    SetActorLocation(NewLocation);
}


void ABLCameraSpectatorPawn::MoveCameraRight(float Direction)
{
    float MovementValue = Direction * CameraMovementSpeed;
    FVector DeltaMovement = MovementValue * (FRotator(0.0f, 90.0f, 0.0f) + GetIsolatedCameraYaw()).Vector();
    FVector NewLocation = GetActorLocation() + DeltaMovement;

    SetActorLocation(NewLocation);
}


FRotator ABLCameraSpectatorPawn::GetIsolatedCameraYaw()
{
    // FRotator containing Yaw only
    return FRotator(0.0f, CameraComponent->ComponentToWorld.Rotator().Yaw, 0.0f);
}

//---------------

void ABLCameraSpectatorPawn::MoveCameraUp(float Direction)
{
    float MovementValue = Direction * CameraMovementSpeed;
    FVector DeltaMovement = FVector(0.0f, 0.0f, MovementValue);
    FVector NewLocation = GetActorLocation() + DeltaMovement;
    NewLocation.Z = FMath::Clamp(NewLocation.Z, CameraRadiusMin, CameraRadiusMax);

    SetActorLocation(NewLocation);
}

//---------------

void ABLCameraSpectatorPawn::ZoomCameraIn(float Direction)
{
    float MovementValue = Direction * CameraMovementSpeed;                // zoom speed is too low here
    CameraRadius += MovementValue;
    CameraRadius = FMath::Clamp(CameraRadius, CameraRadiusMin, CameraRadiusMax);

    RepositionCamera();
}


void ABLCameraSpectatorPawn::TurnCameraUp(float Direction)
{
    CameraHeightAngle -= Direction * CameraRotationSpeed * 10.0f;        // rotation speed is too low
    CameraHeightAngle = FMath::Clamp(CameraHeightAngle, CameraHeightAngleMin, CameraHeightAngleMax);

    RepositionCamera();
}


void ABLCameraSpectatorPawn::TurnCameraRight(float Direction)
{
    CameraZAnlge += Direction * CameraRotationSpeed * 10.0f;            // rotation speed is too low here

    RepositionCamera();
}


//////////////////////////////////////////////////////////////////


void ABLCameraSpectatorPawn::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
	/*
    // mouse position and screen size
    FVector2D MousePosition;
    FVector2D ViewportSize;

    UGameViewportClient* GameViewport = GEngine->GameViewport;
    
    check(GameViewport);
    GameViewport->GetViewportSize(ViewportSize);

    // if viewport is focused, contains the mouse, and camera movement is allowed
    if (	GameViewport->IsFocused(GameViewport->Viewport) && 
            GameViewport->GetMousePosition(MousePosition) && 
            bCanMoveCamera)
    {
        // movement direction
        if (MousePosition.X < CameraScrollBoundary)
        {
            MoveRightValue = -1.0f;
        }
        else if (ViewportSize.X - MousePosition.X < CameraScrollBoundary)
        {
            MoveRightValue = 1.0f;
        }
        
        if (MousePosition.Y < CameraScrollBoundary)
        {
            MoveForwardValue = 1.0f;
        }
        else if (ViewportSize.Y - MousePosition.Y < CameraScrollBoundary)
        {
            MoveForwardValue = -1.0f;
        }

        // rotate
        if (RotateValue != 0.0f)
        {
            TurnCameraUp(MoveForwardValue * FastMoveValue * DeltaSeconds);
            TurnCameraRight(MoveRightValue * FastMoveValue * DeltaSeconds);
        }
        // move horizontal
        else
        {
            MoveCameraForward(MoveForwardValue * FastMoveValue * DeltaSeconds);
            MoveCameraRight(MoveRightValue * FastMoveValue * DeltaSeconds);
        }
        
        // move vertical
        MoveCameraUp(MoveUpValue * FastMoveValue * DeltaSeconds);

        // zoom
        ZoomCameraIn(ZoomInValue * FastMoveValue * DeltaSeconds);
    }*/
}




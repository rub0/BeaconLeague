// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SpectatorPawn.h"
#include "BLCameraSpectatorPawn.generated.h"

/**
 * 
 */
UCLASS()
class BEACONLEAGUE_API ABLCameraSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()
	
	//------------------------------------

	/** Constructor */
	ABLCameraSpectatorPawn(const FObjectInitializer& ObjectInitializer);

private:

	/** Sets up player inputs
	*    @param InputComponent - Input Component
	*/
	void SetupPlayerInputComponent(class UInputComponent* InputComponent);

	//------------------------------------

public:

	/** Zooms In The Camera */
	UFUNCTION()
	void ZoomInByWheel();

	/** Zooms Out The Camera */
	UFUNCTION()
	void ZoomOutByWheel();

	/** Rotate The Camera Left */
	UFUNCTION()
	void RotateLeftByWheel();

	/** Rotate The Camera Right */
	UFUNCTION()
	void RotateRightByWheel();

	/** Rotate The Camera Up */
	UFUNCTION()
	void RotateUpByWheel();

	/** Rotate The Camera Down */
	UFUNCTION()
	void RotateDownByWheel();

	//---

	/** Calculates the new Location and Rotation of The Camera */
	UFUNCTION()
	void RepositionCamera();

	//------------------------------------

private:

	// set them to +/-1 to get player input from keyboard
	float FastMoveValue;                                            // movement speed multiplier : 1 if shift unpressed, 2 is pressed
	float RotateValue;                                                // turn instead of move camera

	float MoveForwardValue;
	float MoveRightValue;
	float MoveUpValue;
	float ZoomInValue;

	//---

public:

	/** Left or Right Shift is pressed
	* @param direcation - (1.0 for Right, -1.0 for Left)
	*/
	UFUNCTION()
	void FastMoveInput(float Direction);

	/** Left or Right Ctrl is pressed
	* @param direcation - (1.0 for Right, -1.0 for Left)
	*/
	UFUNCTION()
	void RotateInput(float Direction);

	/** Input recieved to move the camera forward
	* @param direcation - (1.0 for forward, -1.0 for backward)
	*/
	UFUNCTION()
	void MoveCameraForwardInput(float Direction);

	/** Input recieved to move the camera right
	* @param direcation - (1.0 for right, -1.0 for left)
	*/
	UFUNCTION()
	void MoveCameraRightInput(float Direction);

	/** Input recieved to move the camera right
	* @param direcation - (1.0 for right, -1.0 for left)
	*/
	UFUNCTION()
	void MoveCameraUpInput(float Direction);

	/** Input recieved to move the camera right
	* @param direcation - (1.0 for right, -1.0 for left)
	*/
	UFUNCTION()
	void ZoomCameraInInput(float Direction);

	/** Input recieved to move the camera right
	* @param direcation - (1.0 for right, -1.0 for left)
	*/
	UFUNCTION()
	void OnMouseClick();

	//---

private:

	/** Moves the camera forward
	* @param direcation - (+ forward, - backward)
	*/
	UFUNCTION()
	void MoveCameraForward(float Direction);

	/** Moves the camera right
	* @param direcation - (+ right, - left)
	*/
	UFUNCTION()
	void MoveCameraRight(float Direction);

	/** Gets the roatation of the camera with only the yaw value
	* @return - returns a rotator that is (0, yaw, 0) of the Camera
	*/
	UFUNCTION()
	FRotator GetIsolatedCameraYaw();

	//---

	/** Moves the camera up/down
	* @param direcation - (+ up, - down)
	*/
	UFUNCTION()
	void MoveCameraUp(float Direction);

	//---

	/** Zooms the camera in/out
	* @param direcation - (+ in, - out)
	*/
	UFUNCTION()
	void ZoomCameraIn(float Direction);

	/** Turns the camera up/down
	* @param direcation - (+ up, - down)
	*/
	UFUNCTION()
	void TurnCameraUp(float Direction);

	/** Turns the camera right/left
	* @param direcation - (+ right, - left)
	*/
	UFUNCTION()
	void TurnCameraRight(float Direction);

	//------------------------------------

public:

	/** Tick Function, handles keyboard inputs */
	UFUNCTION()
	virtual void Tick(float DeltaSeconds) override;

	//------------------------------------
public:

	/** Camera Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* CameraComponent;

	/** Camera Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArm;

	//------------------------------------

	/** Camera Rotation around Axis Z */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraZAnlge;

	/** Camera Height Angle */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraHeightAngle;

	/** Camera Pitch Angle Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraHeightAngleMax;

	/** Camera Pitch Angle Min */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraHeightAngleMin;

	/** Camera Radius From Pawn Position */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraRadius;

	/** Camera Radius Max */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraRadiusMax;

	/** Camera Radius Min */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraRadiusMin;

	/** Camera Zoom Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraZoomSpeed;

	/** Camera Rotation Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraRotationSpeed;

	/** Camera Movement Speed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraMovementSpeed;

	/** Camera Scroll Boundary */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float CameraScrollBoundary;

	/** Should the camera move? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	bool bCanMoveCamera;

	/** Should the camera move? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Position)
	FVector bCameraPosition;
};

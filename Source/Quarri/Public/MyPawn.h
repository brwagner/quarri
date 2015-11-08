// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class QUARRI_API AMyPawn : public APawn
{
	GENERATED_BODY()

	// Sets default values for this pawn's properties
	AMyPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere)
	UCameraComponent* OurCamera;

	//Input functions
	void TurnLeft();
	void TurnRight();
	void MoveForward();

	// gets a vector from the direction we're currently facing
	FVector DirToVector();

private:
	const float MOVE_SPEED = 5;
	const float MOVE_DISTANCE = 100;
	enum DIRECTIONS { UP, RIGHT, DOWN, LEFT};
	DIRECTIONS dir = UP;
	FVector DesiredLocation;
	FRotator DesiredRotation; // use yaw
	FRotator GetCurrentRotation(); // rotation of OurVisibleComponent

	/** NOT IN USE
	bool IsMoving();
	bool IsTurning();
	bool IsMovingOrTurning();
	**/

	void Move(FVector Direction, float AxisValue);
};
// Fill out your copyright notice in the Description page of Project Settings.

#include "Quarri.h"
#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->AttachTo(RootComponent);
	OurVisibleComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	// Initialize desired location
	DesiredLocation = GetActorLocation();
	DesiredRotation = GetCurrentRotation();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(FMath::Lerp(GetActorLocation(), DesiredLocation, 0.1f));
	OurVisibleComponent->SetWorldRotation(FMath::Lerp(GetCurrentRotation(), DesiredRotation, 0.1f));
}


// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("Left", IE_Pressed, this, &AMyPawn::TurnLeft);
	InputComponent->BindAction("Right", IE_Pressed, this, &AMyPawn::TurnRight);
	InputComponent->BindAction("Forward", IE_Pressed, this, &AMyPawn::MoveForward);
}

// begin rotating 90 degrees left relative to current rotation
void AMyPawn::TurnLeft()
{
	int res = ((((dir - 1) % 4) + 4) % 4); // modulo a second time to account for negatives
	dir = DIRECTIONS(res);
	DesiredRotation.Yaw = DesiredRotation.Yaw - 90.0f;
}

// begin rotating 90 degrees right relative to current rotation
void AMyPawn::TurnRight()
{
	dir = DIRECTIONS((dir + 1) % 4);
	DesiredRotation.Yaw = DesiredRotation.Yaw + 90.0f;
}

// begin to move 100 units forward based on current direction
void AMyPawn::MoveForward()
{
	DesiredLocation = GetActorLocation() + DirToVector() * MOVE_DISTANCE;
}

/** NOT IN USE
// are we in the middle of moving forward?
bool AMyPawn::IsMoving()
{
	return FVector::Dist(GetActorLocation(), DesiredLocation) > 3.0f;
}

// are we in the middle of turning?
bool AMyPawn::IsTurning()
{
	return FMath::Abs(GetCurrentRotation().Yaw - DesiredRotation.Yaw) > 3.0f;
}

bool AMyPawn::IsMovingOrTurning() {
	return IsMoving() || IsTurning();
}
**/

FVector AMyPawn::DirToVector()
{
	switch (dir) {
	case DIRECTIONS::UP: return FVector::ForwardVector; break;
	case DIRECTIONS::RIGHT: return FVector::RightVector; break;
	case DIRECTIONS::DOWN: return FVector::ForwardVector * -1; break;
	case DIRECTIONS::LEFT: return FVector::RightVector * -1; break;
	default: return FVector::ZeroVector; break;
	}

}

FRotator AMyPawn::GetCurrentRotation()
{
	return OurVisibleComponent->GetComponentRotation();
}
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
}

// Called every frame
void AMyPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (IsMoving()) {
		SetActorLocation(FMath::Lerp(GetActorLocation(), DesiredLocation, 0.1f));
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveX", this, &AMyPawn::MoveXAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::MoveYAxis);
}

void AMyPawn::MoveXAxis(float AxisValue)
{
	Move(FVector::ForwardVector, AxisValue);
}

void AMyPawn::MoveYAxis(float AxisValue)
{
	Move(FVector::RightVector, AxisValue);
}

bool AMyPawn::IsMoving()
{
	return FVector::Dist(GetActorLocation(), DesiredLocation) > 3.0f;
}

void AMyPawn::Move(FVector Direction, float AxisValue)
{
	if (!IsMoving()) {
		float ClampedAxisValue = FMath::Clamp(AxisValue, -1.0f, 1.0f);
		DesiredLocation = GetActorLocation() + Direction * ClampedAxisValue * MOVE_DISTANCE;
	}
}
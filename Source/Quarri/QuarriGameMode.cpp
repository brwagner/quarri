// Fill out your copyright notice in the Description page of Project Settings.

#include "Quarri.h"
#include "QuarriGameMode.h"

void AQuarriGameMode::BeginPlay()
{
	TMap<FVector, TSubclassOf<class AActor>> LayoutConfig;
	LayoutConfig.Add(FVector(0,0,0), Player);

	LayoutConfig.Add(FVector(2, 0, 0), WallBlock);
	LayoutConfig.Add(FVector(2, 1, 0), WallBlock);
	LayoutConfig.Add(FVector(2, 2, 0), WallBlock);
	LayoutConfig.Add(FVector(2, 3, 0), WallBlock);
	LayoutConfig.Add(FVector(2, 4, 0), WallBlock);

	SetUpLevel(LayoutConfig);
}

void AQuarriGameMode::SetUpLevel(const TMap<FVector, TSubclassOf<class AActor>> & LayoutConfig)
{
	for (TMap<FVector, TSubclassOf<class AActor>>::TConstIterator It = LayoutConfig.CreateConstIterator(); It; ++It) {
		AActor * Spawned = PlaceAt(It->Value, It->Key);
		Layout.Add(It->Key, Spawned);
	}
}

AActor* AQuarriGameMode::PlaceAt(TSubclassOf<class AActor> ToPlace, FVector GridPosition)
{
	FVector NormalizedPosition = GridPosition * 100;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Instigator;
	return GetWorld()->SpawnActor<AActor>(ToPlace, NormalizedPosition, FRotator::ZeroRotator, SpawnParams);
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "QuarriGameMode.generated.h"

/*
 * Created at the beginning of every level and destroyed when a new
 * scene is loaded
 */
UCLASS()
class QUARRI_API AQuarriGameMode : public AGameMode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> Player;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> MovableBlock;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> WallBlock;

	void BeginPlay();

private:
	TMap<FVector, AActor*> Layout;
	AActor* PlaceAt(TSubclassOf<class AActor> ToPlace, FVector GridPosition);
	void SetUpLevel(const TMap<FVector, TSubclassOf<class AActor>> & LayoutConfig);
};

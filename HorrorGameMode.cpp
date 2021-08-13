// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include <Pickupable.h>

// Called when the game starts or when spawned
AHorrorGameMode::AHorrorGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHorrorGameMode::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHorrorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// Note, GetAllActorsOfClass is generally not great for performance, but OK right here.

	AActor* player = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());

	if ((Cast<APlayerCharacter>(player)->CurrentPlayerState == PlayerStateCurrent::Inspecting) && GetWorld()->IsPaused() != true)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		PrimaryActorTick.bTickEvenWhenPaused = true;
	}
	else if ((Cast<APlayerCharacter>(player)->CurrentPlayerState == PlayerStateCurrent::Exploring))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		PrimaryActorTick.bTickEvenWhenPaused = false;
	}
}


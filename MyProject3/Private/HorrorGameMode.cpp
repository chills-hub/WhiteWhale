// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include <Pickupable.h>
#include "InGameHud.h"


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
	playerHud = Cast<AInGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	playerBase = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());
	player = Cast<APlayerCharacter>(playerBase);
}

// Called every frame
void AHorrorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Note, GetAllActorsOfClass is generally not great for performance, but OK right here.
	if (player->CurrentPlayerState == PlayerStateCurrent::Inspecting && playerBase->GetWorld()->IsPaused() != true)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		PrimaryActorTick.bTickEvenWhenPaused = true;
	}
	else if (player->CurrentPlayerState == PlayerStateCurrent::Exploring)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		PrimaryActorTick.bTickEvenWhenPaused = false;
	}

	if ((player->PlayerInInventory))
	{
		playerHud->AccessInventoryScreen(true, false);
		//UGameplayStatics::SetGamePaused(GetWorld(), true);
		//PrimaryActorTick.bTickEvenWhenPaused = true;

	}
	else
	{
		playerHud->AccessInventoryScreen(false, true);
		//UGameplayStatics::SetGamePaused(GetWorld(), false);
		//PrimaryActorTick.bTickEvenWhenPaused = false;
	}
}


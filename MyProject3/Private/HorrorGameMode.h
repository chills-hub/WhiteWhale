// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HorrorGameMode.generated.h"

/**
 * 
 */
UCLASS()
class AHorrorGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AHorrorGameMode();

public:
	virtual void Tick(float DeltaTime) override;

	class AInGameHud* playerHud;
	class APlayerCharacter* player;
	class AActor* playerBase;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
};

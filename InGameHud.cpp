// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHud.h"

AInGameHud::AInGameHud() 
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;
}


void AInGameHud::DrawHUD()
{
	Super::DrawHUD();
}

void AInGameHud::BeginPlay()
{
	Super::BeginPlay();

	if (LowerTextWidgetClass) 
	{
		LowerTextWidget = CreateWidget<UTextWidget>(GetWorld(), LowerTextWidgetClass);
		if (LowerTextWidget)
		{
			LowerTextWidget->AddToViewport();
		}

	}
}

void AInGameHud::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void AInGameHud::UpdateLowerText(FString newText)
{
	if (LowerTextWidget) 
	{
		LowerTextWidget->UpdateWidgetText(newText);
	}
}

void AInGameHud::ResetLowerText()
{
	if (LowerTextWidget)
	{
		LowerTextWidget->ResetWidgetText();
	}
}

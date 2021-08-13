// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TextWidget.h"
#include "GameFramework/HUD.h"
#include "InGameHud.generated.h"


/**
 * 
 */
UCLASS()
class AInGameHud : public AHUD
{
	GENERATED_BODY()

public:
	AInGameHud();

	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

	UFUNCTION()
	void UpdateLowerText(FString newText);

	UFUNCTION()
		void ResetLowerText();

	//Parameter to let us assign our text widget to the hud
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> LowerTextWidgetClass;

private:

	UTextWidget* LowerTextWidget;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TextWidget.h"
#include "UI/InventoryImageWidget.h"
#include "UI/InventoryScreenBackgroundWidget.h"
#include "UI/InventoryScreenItemNameWidget.h"
#include "UI/InventoryScreenItemDescWidget.h"
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

	UFUNCTION()
	void AccessInventoryScreen(bool openInventory, bool isInInventory);

	UFUNCTION()
		void UpdateInventoryItemDesc(FString newText);

	UFUNCTION()
		void UpdateInventoryItemName(FString newText);

	//Parameter to let us assign our text widget to the hud
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> LowerTextWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> InventoryImageClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> InventoryScreenItemNameWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> InventoryScreenItemDescWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> InventoryScreenBackgroundWidgetClass;

private:

	UTextWidget* LowerTextWidget;
	UInventoryImageWidget* InventoryImageWidget;
	UInventoryScreenBackgroundWidget* InventoryScreenBackgroundImageWidget;
	UInventoryScreenItemNameWidget* InventoryScreenItemNameWidget;
	UInventoryScreenItemDescWidget* InventoryScreenItemDescWidget;

};

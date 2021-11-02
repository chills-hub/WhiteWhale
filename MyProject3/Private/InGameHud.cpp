// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHud.h"
#include <PlayerCharacter.h>


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

	if (InventoryScreenBackgroundWidgetClass)
	{
		InventoryScreenBackgroundImageWidget = CreateWidget<UInventoryScreenBackgroundWidget>(GetWorld(), InventoryScreenBackgroundWidgetClass);

		if (InventoryScreenBackgroundImageWidget)
		{
			InventoryScreenBackgroundImageWidget->AddToViewport();
			InventoryScreenBackgroundImageWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (InventoryImageClass)
	{
		InventoryImageWidget = CreateWidget<UInventoryImageWidget>(GetWorld(), InventoryImageClass);
		//Assign the mesh from the inventory slot here?
		if (InventoryImageWidget)
		{
			InventoryImageWidget->AddToViewport();
			InventoryImageWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (InventoryScreenItemNameWidgetClass)
	{
		InventoryScreenItemNameWidget = CreateWidget<UInventoryScreenItemNameWidget>(GetWorld(), InventoryScreenItemNameWidgetClass);
		if (InventoryScreenItemNameWidget)
		{
			InventoryScreenItemNameWidget->AddToViewport();
			InventoryScreenItemNameWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (InventoryScreenItemDescWidgetClass)
	{
		InventoryScreenItemDescWidget = CreateWidget<UInventoryScreenItemDescWidget>(GetWorld(), InventoryScreenItemDescWidgetClass);
		if (InventoryScreenItemDescWidget)
		{
			InventoryScreenItemDescWidget->AddToViewport();
			InventoryScreenItemDescWidget->SetVisibility(ESlateVisibility::Hidden);
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

void AInGameHud::UpdateInventoryItemName(FString newText)
{
	if (InventoryScreenItemNameWidget)
	{
		InventoryScreenItemNameWidget->UpdateWidgetText(newText);
	}
}

void AInGameHud::UpdateInventoryItemDesc(FString newText)
{
	if (InventoryScreenItemDescWidget)
	{
		InventoryScreenItemDescWidget->UpdateWidgetText(newText);
	}
}

void AInGameHud::AccessInventoryScreen(bool openInventory, bool isInInventory)
{
	if (!isInInventory && openInventory)
	{
		InventoryImageWidget->SetVisibility(ESlateVisibility::Visible);
		InventoryScreenBackgroundImageWidget->SetVisibility(ESlateVisibility::Visible);
		InventoryScreenItemDescWidget->SetVisibility(ESlateVisibility::Visible);
		InventoryScreenItemNameWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else if (isInInventory && !openInventory)
	{
		InventoryImageWidget->SetVisibility(ESlateVisibility::Hidden);
		InventoryScreenBackgroundImageWidget->SetVisibility(ESlateVisibility::Hidden);
		InventoryScreenItemDescWidget->SetVisibility(ESlateVisibility::Hidden);
		InventoryScreenItemNameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

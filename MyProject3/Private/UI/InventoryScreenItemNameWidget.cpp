// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryScreenItemNameWidget.h"

UInventoryScreenItemNameWidget::UInventoryScreenItemNameWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UInventoryScreenItemNameWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryScreenItemNameWidget::UpdateWidgetText(FString newText)
{

	if (ItemName->Visibility == ESlateVisibility::Hidden)
	{
		ItemName->Visibility = ESlateVisibility::Visible;
	}

	ItemName->SetText(FText::FromString(newText));
}

void UInventoryScreenItemNameWidget::ResetWidgetText()
{
	if (ItemName)
	{
		ItemName->Visibility = ESlateVisibility::Hidden;
		ItemName->SetText(FText::FromString(""));
	}
}
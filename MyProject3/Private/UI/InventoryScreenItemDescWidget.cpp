// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryScreenItemDescWidget.h"
#include "Components/TextBlock.h"

UInventoryScreenItemDescWidget::UInventoryScreenItemDescWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UInventoryScreenItemDescWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryScreenItemDescWidget::UpdateWidgetText(FString newText)
{

	if (ItemDescription->Visibility == ESlateVisibility::Hidden)
	{
		ItemDescription->Visibility = ESlateVisibility::Visible;
	}

	ItemDescription->SetText(FText::FromString(newText));
}

void UInventoryScreenItemDescWidget::ResetWidgetText()
{
	if (ItemDescription)
	{
		ItemDescription->Visibility = ESlateVisibility::Hidden;
		ItemDescription->SetText(FText::FromString(""));
	}
}
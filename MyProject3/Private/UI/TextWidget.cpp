// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TextWidget.h"
#include "Components/TextBlock.h"


UTextWidget::UTextWidget(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{

}

void UTextWidget::NativeConstruct() 
{
	Super::NativeConstruct();
}

void UTextWidget::UpdateWidgetText(FString newText) 
{

	if (LowerText->Visibility == ESlateVisibility::Hidden) 
	{
		LowerText->Visibility = ESlateVisibility::Visible;
	}

	LowerText->SetText(FText::FromString(newText));
}

void UTextWidget::ResetWidgetText()
{
	if (LowerText)
	{
		LowerText->Visibility = ESlateVisibility::Hidden;
		LowerText->SetText(FText::FromString(""));
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/TextWidget.h"
#include "Blueprint/UserWidget.h"
#include "InventoryScreenItemDescWidget.generated.h"

/**
 * 
 */
UCLASS()
class UInventoryScreenItemDescWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UInventoryScreenItemDescWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

public:

	void UpdateWidgetText(FString newText);

	void ResetWidgetText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ItemDescription;
};

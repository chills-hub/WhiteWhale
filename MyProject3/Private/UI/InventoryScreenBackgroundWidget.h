// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryScreenBackgroundWidget.generated.h"

/**
 * 
 */
UCLASS()
class UInventoryScreenBackgroundWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UInventoryScreenBackgroundWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* InventoryScreenBackgroundImage;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryImageWidget.generated.h"

/**
 * 
 */
UCLASS()
class UInventoryImageWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UInventoryImageWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UImage* InventoryImage;
};

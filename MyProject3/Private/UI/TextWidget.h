// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextWidget.generated.h"

/**
 * 
 */
UCLASS()
class UTextWidget : public UUserWidget
{
	GENERATED_BODY()

	UTextWidget(const FObjectInitializer& objectInitializer);

	virtual void NativeConstruct() override;

public:
	void UpdateWidgetText(FString newText);

	void ResetWidgetText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* LowerText;
};

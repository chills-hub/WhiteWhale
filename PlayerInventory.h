// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PlayerInventory
{
public:
	PlayerInventory();
	~PlayerInventory();

	UFUNCTION()
	void AddToInventory(AActor* item);

	TArray<AActor*> Inventory;
};

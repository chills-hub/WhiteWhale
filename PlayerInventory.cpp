// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

PlayerInventory::PlayerInventory()
{

}

PlayerInventory::~PlayerInventory()
{
}

void PlayerInventory::AddToInventory(AActor* item)
{
	Inventory.Add(item);
}
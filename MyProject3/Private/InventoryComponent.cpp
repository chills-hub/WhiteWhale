// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/MeshComponent.h"
#include "InventoryComponent.h"
#include <InGameHud.h>
#include "EngineUtils.h"
#include <InventoryModelDisplayActor.h>
#include <Pickupable.h>

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	 
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AInventoryModelDisplayActor> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
	{
		InventoryDisplayModelActor = *ActorIterator;
	}
	Inventory.Add(Cast<AActor>(Flashlight_Default->GetDefaultObject()));
	InGameHud = Cast<AInGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int UInventoryComponent::AddToInventory(AActor* item)
{
	Inventory.Add(item);
	return 0;
}

int UInventoryComponent::UpdateInventoryDisplayModel()
{
	int InventoryNum = 0;


	if (CurrentInventoryNum != 0)
	{
		InventoryNum = CurrentInventoryNum;
	}

	AActor* inventoryItem = Inventory[InventoryNum];
	APickupable* pickup = Cast<APickupable>(inventoryItem);

	if (inventoryItem == nullptr)
	{
		inventoryItem = Inventory[0];
	}

	//AActor* displayModelTest = Cast<AActor>(InventoryDisplayModelActor);

	UActorComponent* itemComponent = inventoryItem->GetComponentByClass(UStaticMeshComponent::StaticClass());
	UStaticMeshComponent* itemMeshComp = Cast<UStaticMeshComponent>(itemComponent);
	UStaticMesh* itemMesh = itemMeshComp->GetStaticMesh();

	UActorComponent* displayModelComponent = InventoryDisplayModelActor->GetComponentByClass(UStaticMeshComponent::StaticClass());
	UStaticMeshComponent* displayModelMesh = Cast<UStaticMeshComponent>(displayModelComponent);
	displayModelMesh->SetStaticMesh(itemMesh);
	InGameHud->UpdateInventoryItemName(pickup->ObjectName);
	InGameHud->UpdateInventoryItemDesc(pickup->ObjectDescription);
	return 0;
}


int UInventoryComponent::TraverseInventoryLeft()
{
	if (CurrentInventoryNum - 1 < 0)
	{
		CurrentInventoryNum = Inventory.Num() - 1;
	}
	else
	{
		CurrentInventoryNum--;
	}
	UpdateInventoryDisplayModel();
	return 0;
}


int UInventoryComponent::TraverseInventoryRight()
{
	if (CurrentInventoryNum + 1 > Inventory.Num() - 1)
	{
		CurrentInventoryNum = 0;
	}
	else
	{
		CurrentInventoryNum++;
	}
	UpdateInventoryDisplayModel();
 	return 0;
}

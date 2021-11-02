// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryInterface.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UInventoryComponent : public UActorComponent, public IInventoryInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(VisibleDefaultsOnly)
		class AInventoryModelDisplayActor* InventoryDisplayModelActor;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> Inventory;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> Flashlight_Default;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int AddToInventory(AActor* item) override;
	int UpdateInventoryDisplayModel() override;
	int TraverseInventoryRight() override;
	int TraverseInventoryLeft() override;
	int CurrentInventoryNum;
	class AInGameHud* InGameHud;


};

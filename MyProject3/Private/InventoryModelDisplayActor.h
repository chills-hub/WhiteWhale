// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryModelDisplayActor.generated.h"

UCLASS()
class AInventoryModelDisplayActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AInventoryModelDisplayActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* InventoryDisplayModel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneCaptureComponent2D* InventoryCamera;

	UPROPERTY(EditAnywhere, Category = Movement)
		float YawValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickupable.generated.h"


UCLASS()
class APickupable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupable();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void Inspect();

	UFUNCTION()
	void PickUp();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ObjectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectInspectText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectPickupText;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	friend class APlayerCharacter;
};

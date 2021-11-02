// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "HorrorGameMode.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InventoryModelDisplayActor.h"

// Sets default values
AInventoryModelDisplayActor::AInventoryModelDisplayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("InventoryCamera"));
	InventoryDisplayModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InventoryModel"));
	YawValue = 0.f;
}

// Called when the game starts or when spawned
void AInventoryModelDisplayActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInventoryModelDisplayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = FRotator(0.f, YawValue, 0.f);
	FQuat QuatRotation = FQuat(NewRotation);
	InventoryDisplayModel->AddLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}


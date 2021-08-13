// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickupable.h"
#include "InGameHud.h"

FString ObjectInspectText;

// Sets default values
APickupable::APickupable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	PickupMesh->ComponentTags.Add("KeyItem");

	
}

// Called when the game starts or when spawned
void APickupable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickupable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupable::Inspect()
{
	AInGameHud* InGameHud = Cast<AInGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (InGameHud)
	{
		InGameHud->UpdateLowerText(ObjectInspectText);
	}
}

void APickupable::PickUp()
{
	AInGameHud* InGameHud = Cast<AInGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (InGameHud)
	{
		ObjectPickupText = ObjectPickupText += ObjectName;
		InGameHud->UpdateLowerText(ObjectPickupText);
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "InGameHud.h"
#include "InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include <Pickupable.h>

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	SetupCamera();

	SphereColliderForInteract = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	SphereColliderForInteract->SetupAttachment(RootComponent);
	SphereColliderForInteract->SetSphereRadius(120.f, true);
	SphereColliderForInteract->SetActive(true);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	//don't rotate the mesh with the camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Change the mesh rotation base on the button we press to move
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 540, 0);

	TurnRate = 45.f;
	LookRate = 45.f;
	PlayerInInventory = false;
	FlashlightOn = false;
}

void APlayerCharacter::SetupCamera()
{
	BoomArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	BoomArm->SetupAttachment(RootComponent);
	BoomArm->TargetArmLength = 100.f;
	BoomArm->SocketOffset = FVector(CameraSocketOffsetX, CameraSocketOffsetY, CameraSocketOffsetZ);
	BoomArm->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	//socketname parameter is the name of the socket at the end of the spring arm
	PlayerCamera->SetupAttachment(BoomArm, USpringArmComponent::SocketName);
	PlayerCamera->bUsePawnControlRotation = false;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ForwardValue == 0.0 && RightValue == 0.0) 
	{
		IsIdle = true;
		IsWalking = false;
		IsRunning = false;
	}

	if (ForwardValue != 0.0 || RightValue != 0.0)
	{
		IsIdle = false;
		if (IsRunning != true) 
		{
			IsWalking = true;
		}
		else if (IsRunning == true)
		{
			IsWalking = false;
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
#if WITH_EDITOR
	check(PlayerInputComponent);
#endif

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Run", this, &APlayerCharacter::CheckForRun); 	//THIS IS AN AXIS BIND TO ALLOW HOLDING THE BUTTON TO SPRINT
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::Interact).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Flashlight", IE_Pressed, this, &APlayerCharacter::ClickFlashlight);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &APlayerCharacter::OpenInventory);
	PlayerInputComponent->BindAction("Inventory_Left", IE_Pressed, this, &APlayerCharacter::TraverseInventoryLeft).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("Inventory_Right", IE_Pressed, this, &APlayerCharacter::TraverseInventoryRight).bExecuteWhenPaused = true;
}

void APlayerCharacter::MoveForward(float value)
{
	ForwardValue = value;
	if (Controller != NULL && value != 0.0) 
	{
		SpeedMultiplier = AdjustSpeed(value);
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
		AddMovementInput(direction, SpeedMultiplier);
	}
}

void APlayerCharacter::MoveRight(float value)
{
	RightValue = value;
	if (Controller != NULL && value != 0.0)
	{
		SpeedMultiplier = AdjustSpeed(value);
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator Yaw(0, rotation.Yaw, 0);
		const FVector direction = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, SpeedMultiplier);
	}
}

void APlayerCharacter::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * GetWorld()->GetDeltaSeconds() * TurnRate);
}

void APlayerCharacter::LookUpAtRate(float rate)
{
	AddControllerPitchInput(rate * GetWorld()->GetDeltaSeconds() * LookRate);
}

void APlayerCharacter::CheckForRun(float value)
{
	if (value == 1 && IsIdle == false)
	{
		IsRunning = true;
	}
	else
	{
		IsRunning = false;
	}
}

void APlayerCharacter::Interact()
{
	TArray<AActor*> ItemsInRange;
	SphereColliderForInteract->GetOverlappingActors(ItemsInRange);
	AInGameHud* InGameHud = Cast<AInGameHud>(GetWorld()->GetFirstPlayerController()->GetHUD());
	IInventoryInterface* TheInterface = Cast<IInventoryInterface>(InventoryComponent);
	float lastDistance = 0.f;
	float currentDistance = 0.f;
	AActor* closestObject = nullptr;

	if (ItemsInRange.Num() < 1)
	{
		CurrentPlayerState = PlayerStateCurrent::Exploring;
		InGameHud->ResetLowerText();
		return;
	}
	else
	{
		if (CurrentPlayerState == PlayerStateCurrent::Inspecting)
		{
			CurrentPlayerState = PlayerStateCurrent::Exploring;
			InGameHud->ResetLowerText();
		}
		else
		{
			for (AActor* actor : ItemsInRange)
			{
				currentDistance = actor->GetDistanceTo(this);

				if (currentDistance < lastDistance || lastDistance == 0.f)
				{
					lastDistance = currentDistance;
					closestObject = actor;
				}
			}

			if (closestObject != NULL)
			{
				CurrentPlayerState = PlayerStateCurrent::Inspecting;

				if (closestObject->Tags.Contains("EnvironmentItem"))
				{
					Cast<APickupable>(closestObject)->Inspect();
				}
				if (closestObject->Tags.Contains("KeyItem"))
				{				
					Cast<APickupable>(closestObject)->PickUp();

					if (TheInterface)
					{
						TheInterface->AddToInventory(closestObject);
					}
				}
			}
		}
	}
}

void APlayerCharacter::OpenInventory()
{
	CurrentPlayerState = PlayerStateCurrent::Inventory;
	IInventoryInterface* TheInterface = Cast<IInventoryInterface>(InventoryComponent);

	if (!PlayerInInventory) 
	{
		PlayerInInventory = true;
		TheInterface->UpdateInventoryDisplayModel();
	}
	else if (PlayerInInventory)
	{
		PlayerInInventory = false;
	}
}

void  APlayerCharacter::ClickFlashlight() 
{
	if (!FlashlightOn)
	{
		FlashlightOn = true;
	}
	else
	{
		FlashlightOn = false;
	}
}

void APlayerCharacter::TraverseInventoryLeft()
{
	if (CurrentPlayerState == PlayerStateCurrent::Inventory)
	{
		IInventoryInterface* TheInterface = Cast<IInventoryInterface>(InventoryComponent);
		TheInterface->TraverseInventoryLeft();
	}
}

void APlayerCharacter::TraverseInventoryRight()
{
	if (CurrentPlayerState == PlayerStateCurrent::Inventory)
	{
		IInventoryInterface* TheInterface = Cast<IInventoryInterface>(InventoryComponent);
		TheInterface->TraverseInventoryRight();
	}
}

#pragma region Helper Methods

float APlayerCharacter::AdjustSpeed(float multiplier)
{
	if (IsRunning)
	{
		return multiplier;
	}
	else
	{
		return multiplier / 4.f;
	}
}

#pragma endregion
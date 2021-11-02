// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
	//"class" keyword here is for forward declaration, we define/include these classes in the CPP file, this will speed up compilation
	//meta = (AllowPrivateAccess = "true") allows these uproperties to be accessible from blueprints?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* BoomArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereColliderForInteract;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//movement rates
	UPROPERTY()
	float TurnRate;

	UPROPERTY()
	float LookRate;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CameraSocketOffsetX;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CameraSocketOffsetY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CameraSocketOffsetZ;

	//player state bools
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsRunning;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsIdle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsWalking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool FlashlightOn;



	//player state floats
	//the values of the inputs for movement for idle checks
	float ForwardValue;
	float RightValue;
	float SpeedMultiplier;
	bool PlayerInInventory;



	PlayerStateCurrent CurrentPlayerState;

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void TurnAtRate(float rate);
	void LookUpAtRate(float rate);
	void CheckForRun(float value);
	void Interact();
	void OpenInventory();
	void TraverseInventoryLeft();
	void TraverseInventoryRight();
	void ClickFlashlight();

private:
	void SetupCamera();
	float AdjustSpeed(float multiplier);
};

UENUM()
enum class PlayerStateCurrent
{
	Exploring     UMETA(DisplayName = "Exploring"),
	Inspecting      UMETA(DisplayName = "Inspecting"),
	Inventory      UMETA(DisplayName = "Inventory"),
};
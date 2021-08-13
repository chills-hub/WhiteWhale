// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerInventory.h"
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
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//movement rates
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float LookRate;

	//player state bools
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsRunning;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsIdle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool IsWalking;

	//player state floats
	//the values of the inputs for movement for idle checks
	float ForwardValue;
	float RightValue;
	float SpeedMultiplier;
	bool SwitchFlashLight;

	PlayerStateCurrent CurrentPlayerState;
	PlayerInventory Inventory;

	class UPointLightComponent* PointLight;
	class USpotLightComponent* Spotlight;


protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float value);
	void MoveRight(float value);
	void TurnAtRate(float rate);
	void LookUpAtRate(float rate);
	void CheckForRun(float value);
	void Interact();
	void FlashlightSwitch();
	float AdjustSpeed(float multiplier);

private:


};

UENUM()
enum class PlayerStateCurrent
{
	Exploring     UMETA(DisplayName = "Exploring"),
	Inspecting      UMETA(DisplayName = "Inspecting"),
};
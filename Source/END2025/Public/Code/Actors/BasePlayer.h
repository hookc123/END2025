// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABasePlayer();
protected:
	/** The Spring Arm component that controls camera distance and rotation */
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	/** The Camera component attached to the Spring Arm */
	UPROPERTY(Category = "Default", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void InputAxisMoveForward(float AxisValue);
	void InputAxisStrafe(float AxisValue);
};

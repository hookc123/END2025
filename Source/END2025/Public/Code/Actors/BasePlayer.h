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
	// Add a SpringArmComponent to the player
	class USpringArmComponent* SpringArm;
	// Add a CameraComponent to the SpringArmComponent
	class UCameraComponent* Camera;
};

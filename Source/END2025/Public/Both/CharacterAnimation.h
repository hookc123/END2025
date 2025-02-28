// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Defaults")
	bool DebugFire = false;

protected:

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void FireAnimation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
	UAnimSequenceBase* FireAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
	FName ActionSlotName = "Action";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
	float velocity = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
	float direction = 0.0f;


	UFUNCTION(BlueprintNativeEvent)
	void PreviewWindowUpdate();
	virtual void PreviewWindowUpdate_Implementation();
};

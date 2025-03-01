// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class END2025_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
public:



protected:

	UPROPERTY(BlueprintReadOnly, Category = HUD, meta = (BindWidget))
	class UProgressBar* HealthBar;

private:



};

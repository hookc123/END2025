// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/PlayerHUD.h"
#include "Components/ProgressBar.h"

void UPlayerHUD::SetHealth(float p)
{
	HealthBar->SetPercent(p);
}

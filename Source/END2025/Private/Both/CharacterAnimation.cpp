// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"
#include "KismetAnimationLibrary.h"

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* pawn = TryGetPawnOwner();
	if (pawn)
	{
		// Is Valid

		FVector returnValue = pawn->GetVelocity();
		velocity = returnValue.Size();
		direction = UKismetAnimationLibrary::CalculateDirection(pawn->GetVelocity(), pawn->GetActorRotation());
	}
		// Not Valid
		PreviewWindowUpdate();
}

void UCharacterAnimation::FireAnimation()
{
	PlaySlotAnimationAsDynamicMontage(FireAsset,ActionSlotName);
}

void UCharacterAnimation::PreviewWindowUpdate_Implementation()
{
	if (DebugFire)
	{
		DebugFire = !DebugFire;
		FireAnimation();
	}
}

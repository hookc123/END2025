// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* pawn = TryGetPawnOwner();
	if (pawn)
	{
		// Is Valid

		FVector returnValue = pawn->GetVelocity();
		velocity = returnValue.Size();
		//FVector lateralSpeed = FVector(velocity.X, velocity.Y, 0.0f);
		//movementSpeed = lateralSpeed.Size();
	}
	else {
		// Not Valid
	}
}

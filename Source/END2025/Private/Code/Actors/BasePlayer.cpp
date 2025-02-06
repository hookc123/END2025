// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ABasePlayer::ABasePlayer()
{
	// Create a SpringArmComponent
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetRelativeLocation(FVector(0., 0., 60.));
	SpringArm->SetupAttachment(GetRootComponent()/*, only need to use this if we are using sockets*/);
	// Create a CameraComponent
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Do not forget to call parent function
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Bind the axis inputs
	
	// Use Pawn Control Rotation in the spring arm
	SpringArm->bUsePawnControlRotation = true;
	PlayerInputComponent->BindAxis("TurnRight"	, this, &ABasePlayer::AddControllerYawInput  );
	PlayerInputComponent->BindAxis("LookUp"		, this, &ABasePlayer::AddControllerPitchInput);
}

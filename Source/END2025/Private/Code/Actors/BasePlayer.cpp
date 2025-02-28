// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Code/Actors/BaseRifle.h"

ABasePlayer::ABasePlayer()
{
	// Create a SpringArmComponent
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetRelativeLocation(FVector(0., 0., 60.));
	SpringArm->SetupAttachment(GetRootComponent()/*, only need to use this if we are using sockets*/);
	// Create a CameraComponent
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);


	WeaponClass = ABaseRifle::StaticClass();
	// Create Child Actor Component
	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>("ChildActorComponent");
	ChildActorComponent->SetupAttachment(GetMesh(), "PlaceWeaponHere");
	//WeaponObject = ChildActorComponent->GetChildActor();//Cast<ABaseRifle>(ChildActorComponent->GetChildActor());
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

	// Player Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::InputAxisMoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &ABasePlayer::InputAxisStrafe);
	
	if (ChildActorComponent) {
		// Set the child actor class
		if (WeaponClass)
		{
			ChildActorComponent->SetChildActorClass(WeaponClass);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ChildActorComponent is not set in %s"), *GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponClass is not set in %s"), *GetName());
	}

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasePlayer::OnFirePressed);
}

void ABasePlayer::OnFirePressed()
{
	CharacterAnimation = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance());
	if (CharacterAnimation)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character Animation is Valid"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Character Animation is not Valid"));
	}
	WeaponObject = Cast<ABaseRifle>(ChildActorComponent->GetChildActor());
	if (WeaponObject)
	{
		Cast<ABaseRifle>(ChildActorComponent->GetChildActor())->Attack();
		if (CharacterAnimation)
		{
			CharacterAnimation->DebugFire = true;
		}
	}

	/*if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (UABP_CharacterAnimation* MyAnimBP = Cast<UABP_CharacterAnimation>(AnimInstance))
		{
			MyAnimBP->FireAnimation();
		}
	}*/
}

void ABasePlayer::InputAxisMoveForward(float AxisValue)
{
	// Get control Rotation
	FRotator Break = GetControlRotation();
	FRotator Make(0., Break.Yaw, 0.);
	FVector WorldDirection = Make.Vector();

	// Move the actor forward
	AddMovementInput(WorldDirection, AxisValue);
	//AddMovementInput(FRotator(0., GetControlRotation().Yaw, 0).Vector(), AxisValue);
}

void ABasePlayer::InputAxisStrafe(float AxisValue)
{
	FRotator Break = GetControlRotation();
	FRotator Make(0., Break.Yaw + 90, 0.);
	FVector WorldDirection = Make.Vector();

	// Strafe the actor 
	AddMovementInput(WorldDirection, AxisValue);
}

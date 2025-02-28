// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseCharacter.h"
#include "Code/Actors/BaseRifle.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GetMesh()->SetRelativeRotation(FRotator(0., -90., 0.));
	GetMesh()->SetRelativeLocation(FVector(0., 0., -90.));

	WeaponClass = ABaseRifle::StaticClass();
	// Create Child Actor Component
	ChildActorComponent = CreateDefaultSubobject<UChildActorComponent>("ChildActorComponent");
	ChildActorComponent->SetupAttachment(GetMesh(), "PlaceWeaponHere");

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

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


}

void ABaseCharacter::OnFirePressed()
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

}


// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


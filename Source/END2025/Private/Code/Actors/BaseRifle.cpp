// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseRifle.h"
#include "Code/Actors/Projectile.h"

// Sets default values
ABaseRifle::ABaseRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Set the skeletal mesh as the root component
	baseRifleMesh = CreateDefaultSubobject<USkeletalMeshComponent>("BaseRifleMesh");
	SetRootComponent(baseRifleMesh);

	// Set the projectile class
	ProjectileClass = AProjectile::StaticClass();

}

// Called when the game starts or when spawned
void ABaseRifle::BeginPlay()
{
	Super::BeginPlay();
	ParentPawn = Cast<APawn>(GetParentActor());
	if (ParentPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Parent Pawn: %s"), *ParentPawn->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Owner Must be A Pawn"));
		Destroy();
	}
}

void ABaseRifle::Attack()
{
	AProjectile* SpawnedProjectile = nullptr;

	FVector pos;
	/*if (baseRifleMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Base Rifle Mesh is set in %s"), *GetName());
		pos = baseRifleMesh->GetSocketLocation(WeaponSocketName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Base Rifle Mesh is not set in %s"), *GetName());
	}*/
	auto rot = ParentPawn->GetBaseAimRotation();
	auto controller = ParentPawn->GetController();
	
	pos = baseRifleMesh->GetSocketLocation(WeaponSocketName);

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = controller;
	spawnParams.Instigator = ParentPawn;

	if(CanShoot())
	SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, pos, rot, spawnParams);

	if (SpawnedProjectile)
	{
		ActionHappening = true;
		UE_LOG(LogTemp, Warning, TEXT("Successfully spawned projectile!"));

		// Define a delegate for the event
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("ActionStopped"));

		// Set a timer that calls ActionStopped using the delegate
		GetWorldTimerManager().SetTimer(timer, TimerDelegate, ResetTime, false);

		// Broadcast to the Delegate CallOnRifleAttack
		CallOnRifleAttack.Broadcast();

	}	
}

void ABaseRifle::ActionStopped()
{
	ActionHappening = false;
}

// Called every frame
void ABaseRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseRifle::CanShoot() const
{
	return !ActionHappening;
}


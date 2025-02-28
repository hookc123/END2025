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

	
	/*if (ProjectileClass)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = controller;
		spawnParams.Instigator = ParentPawn;
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, pos, rot, spawnParams);

		UE_LOG(LogTemp, Warning, TEXT("Projectile Class is set in %s"), *GetName());

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Projectile Class is not set in %s"), *GetName());
	}*/

	pos = baseRifleMesh->GetSocketLocation(WeaponSocketName);

	

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = controller;
	spawnParams.Instigator = ParentPawn;
	auto SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, pos, rot, spawnParams);

	if (SpawnedProjectile)
	{
		UE_LOG(LogTemp, Warning, TEXT("Successfully spawned projectile!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Projectile failed to spawn!"));
	}

}

// Called every frame
void ABaseRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


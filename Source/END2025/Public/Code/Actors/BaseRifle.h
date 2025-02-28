// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRifle.generated.h"

UCLASS()
class END2025_API ABaseRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseRifle();

	//UFUNCTION(BlueprintCallable, Category = Weapon)
	void Attack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Defaults)
	class USkeletalMeshComponent* baseRifleMesh;

	// Parent Pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	APawn* ParentPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AActor> ProjectileClass;

	// Attack function

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName WeaponSocketName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"

// Delegate for health-related events
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHurt, float, DamageAmount);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class END2025_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Handles when the actor takes damage
	UFUNCTION()
	void HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:
	// Health variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	float MaxHealth;

	// Event Dispatchers
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHurt OnHurt;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth;

};
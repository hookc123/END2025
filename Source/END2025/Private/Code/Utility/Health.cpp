#include "Code/Utility/Health.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 5.0f;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	// Set initial health
	CurrentHealth = MaxHealth;

	// Bind to the owning actor's damage event
	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealth::HandleDamage);
	}
}

void UHealth::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f) return;

	CurrentHealth -= Damage;
	OnHurt.Broadcast(Damage);

	if (CurrentHealth <= 0.0f)
	{
		CurrentHealth = 0.0f;
		OnDeath.Broadcast();
	}
}

// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


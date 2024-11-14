#include "CAttributeComponent.h"

UCAttributeComponent::UCAttributeComponent()
{
	SneakSpeed	= 200.f;
	WalkSpeed	= 400.f;
	SprintSpeed = 600.f;

	MaxHealth = 100.f;


	bCanMove = true;

}

void UCAttributeComponent::BeginPlay()
{
	CurrentHealth = MaxHealth;

	Super::BeginPlay();
}

void UCAttributeComponent::SetMove()
{
	bCanMove = true;
}

void UCAttributeComponent::SetStop()
{
	bCanMove = false;
}

void UCAttributeComponent::IncreaseHealth(float InAmount)
{
	CurrentHealth += InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}

void UCAttributeComponent::DecreaseHealth(float InAmount)
{
	CurrentHealth -= InAmount;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.f, MaxHealth);
}

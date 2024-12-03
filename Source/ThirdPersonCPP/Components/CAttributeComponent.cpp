#include "CAttributeComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCAttributeComponent::UCAttributeComponent()
{
	WalkSpeeds[(int32)EWalkSpeedType::Sneak]		= 200.f;
	WalkSpeeds[(int32)EWalkSpeedType::Walk]		= 400.f;
	WalkSpeeds[(int32)EWalkSpeedType::Sprint]	= 600.f;

	MaxHealth = 100.f;

	bCanMove = true;
}

void UCAttributeComponent::BeginPlay()
{
	CurrentHealth = MaxHealth;

	Super::BeginPlay();
}

void UCAttributeComponent::SetSpeed(EWalkSpeedType InType)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(OwnerCharacter);

	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = WalkSpeeds[(int32)InType];
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

#include "CAtionComponent.h"

UCAtionComponent::UCAtionComponent()
{

}


void UCAtionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCAtionComponent::SetUnarmedMode()
{
	ChangeType(EActionType::Unaremd);
}

void UCAtionComponent::SetFistMode()
{
	SetMode(FActionType::Fist);
}

void UCAtionComponent::SetOneHandMode()
{
	SetMode(FActionType::OneHand);
}

void UCAtionComponent::SetTwoHandMode()
{
	SetMode(FActionType::TwoHand);
}

void UCAtionComponent::SetMagicBallMode()
{
	SetMode(FActionType::MagicBall);
}

void UCAtionComponent::SetWrapMode()
{
	SetMode(FActionType::Wrap);
}

void UCAtionComponent::SetWhirlWindMode()
{
	SetMode(FActionType::WhirlWin);
}

void UCAtionComponent::SetMode(EActionType InNewType)
{
	if (Type == InNewType)
	{
		SetUnarmedMode();

		return;
	}
}

void UCAtionComponent::ChangeType(EActionType InNewType)
{
	EActionType PrevType = Type;

	Type = InNewType;

	OnActionTypeChanged.Broadcast(PrevType, Type);
}
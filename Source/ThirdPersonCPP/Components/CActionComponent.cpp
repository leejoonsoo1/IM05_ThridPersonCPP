#include "CActionComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Actions/CActionData.h"
#include "Actions/CEquipment.h"
#include "Actions/CDoAction.h"
#include "Actions/CActionObject.h"

UCActionComponent::UCActionComponent()
{

}

void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());

	for (int32 i = 0; i < (int32)(int32)EActionType::Max; i++)
	{
		if (DataAssets[i] && OwnerCharacter)
		{
			DataAssets[i]->BeginPlay(OwnerCharacter, &DataObjects[i]);
		}
	}
}

void UCActionComponent::PrimaryAction()
{
	CLog::Log("UCActionComponent::PrimaryAction");
	CheckTrue(IsUnarmedMode());

	if (DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetDoAction())
	{
		CLog::Log("DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetDoAction()");
		DataObjects[(int32)Type]->GetDoAction()->PrimaryAction();
	}
}

void UCActionComponent::Begin_SecondaryAction()
{
	CheckTrue(IsUnarmedMode());
	CLog::Log("UCActionComponent::Begin_SecondaryAction");

	if (DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetDoAction())
	{
		CLog::Log("UCActionComponent::Begin_SecondaryAction");

		DataObjects[(int32)Type]->GetDoAction()->Begin_SecondaryAction();
	}
}

void UCActionComponent::End_SecondaryAction()
{
	CheckTrue(IsUnarmedMode());
	if (DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetDoAction())
	{
		DataObjects[(int32)Type]->GetDoAction()->End_SecondaryAction();
	}
}

void UCActionComponent::SetUnarmedMode()
{
	if (DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetEquipment())
	{
		DataObjects[(int32)Type]->GetEquipment()->UnEquip();
	}

	if (DataObjects[(int32)EActionType::Unarmed] && DataObjects[(int32)EActionType::Unarmed]->GetEquipment())
	{
		DataObjects[(int32)EActionType::Unarmed]->GetEquipment()->Equip();
	}

	ChangeType(EActionType::Unarmed);
}

void UCActionComponent::SetFistMode()
{
	SetMode(EActionType::Fist);
}

void UCActionComponent::SetOneHandMode()
{
	SetMode(EActionType::OneHand);
}

void UCActionComponent::SetTwoHandMode()
{
	SetMode(EActionType::TwoHand);
}

void UCActionComponent::SetMagicBallMode()
{
	SetMode(EActionType::MagicBall);
}

void UCActionComponent::SetWarpMode()
{
	SetMode(EActionType::Warp);
}

void UCActionComponent::SetWhirlWindMode()
{
	SetMode(EActionType::WhirlWind);
}

void UCActionComponent::SetMode(EActionType InNewType)
{
	if (Type == InNewType)
	{
		SetUnarmedMode();

		return;
	}
	else if (!IsUnarmedMode())
	{
		if (DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetEquipment())
		{
			DataObjects[(int32)Type]->GetEquipment()->UnEquip(); // Prev Weapon UnEquip
		}
	}
	
	if (DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetEquipment())
	{
		DataObjects[(int32)InNewType]->GetEquipment()->Equip();
	}

	ChangeType(InNewType);
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType PrevType = Type;
	Type = InNewType;


	OnActionTypeChanged.Broadcast(PrevType, Type);
}
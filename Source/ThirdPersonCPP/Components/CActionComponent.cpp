#include "CActionComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Actions/CActionData.h"
#include "Actions/CActionObject.h"
#include "Actions/CEquipment.h"
#include "Actions/CAttachment.h"
#include "Actions/CDoAction.h"

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
	CheckTrue(IsUnarmedMode());

	if (DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetDoAction())
	{
		DataObjects[(int32)Type]->GetDoAction()->PrimaryAction();
	}
}

void UCActionComponent::Begin_SecondaryAction()
{
	CheckTrue(IsUnarmedMode());

	if (DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetDoAction())
	{
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

void UCActionComponent::OffAllCollisions()
{
	for (const auto& Object : DataObjects)
	{
		if (Object && Object->GetAttachment())
		{
			Object->GetAttachment()->OffCollision();
		}
	}
}

void UCActionComponent::DestroyAll()
{
	for (int32 i = 0; i < (int32)EActionType::Max; i++)
	{
		if (DataObjects[i])
		{
			if (DataObjects[i]->GetEquipment())
			{
				DataObjects[i]->GetEquipment()->Destroy();
			}

			if (DataObjects[i]->GetAttachment())
			{
				DataObjects[i]->GetAttachment()->Destroy();
			}

			if (DataObjects[i]->GetDoAction())
			{
				DataObjects[i]->GetDoAction()->Destroy();
			}
		}
	}
}

void UCActionComponent::Abort()
{
	CheckNull(DataObjects[(int32)Type]);
	CheckTrue(IsUnarmedMode());

	if (DataObjects[(int32)Type]->GetEquipment())
	{
		DataObjects[(int32)Type]->GetEquipment()->Begin_Equip();
		DataObjects[(int32)Type]->GetEquipment()->End_Equip();
	}

	if (DataObjects[(int32)Type]->GetDoAction())
	{
		DataObjects[(int32)Type]->GetDoAction()->Abort();
	}
}

void UCActionComponent::SetUnaremdMode()
{
	if (DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetEquipment())
	{
		DataObjects[(int32)Type]->GetEquipment()->Unequip();
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
		SetUnaremdMode();
		return;
	}
	else if (!IsUnarmedMode())
	{
		if (DataObjects[(int32)Type] && DataObjects[(int32)Type]->GetEquipment())
		{
			DataObjects[(int32)Type]->GetEquipment()->Unequip();
		}
	}

	if (DataObjects[(int32)InNewType] && DataObjects[(int32)InNewType]->GetEquipment())
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

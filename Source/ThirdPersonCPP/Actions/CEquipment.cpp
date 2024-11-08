#include "CEquipment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"
#include "Interfaces/CCharacterInterface.h"

ACEquipment::ACEquipment()
{

}

void ACEquipment::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter	= Cast<ACharacter>(GetOwner());
	StateComp		= CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
	AttributeComp	= CHelpers::GetComponent<UCAttributeComponent>(OwnerCharacter);
}

void ACEquipment::SetData(FEquipmentData& InData)
{
	Data = InData;
}

void ACEquipment::SetColor(FLinearColor& InColor)
{
	Color = InColor;
}

void ACEquipment::Equip_Implementation()
{
	StateComp->SetEquipMode();

	Data.bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();

	if (Data.Montage)
	{
		OwnerCharacter->PlayAnimMontage(Data.Montage, Data.PlayRate, Data.StartSection);
	}
	else
	{
		Begin_Equip();
		End_Equip();
	}

	if (Data.bUseControlRotation)
	{
		OwnerCharacter->bUseControllerRotationYaw = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	ICCharacterInterface* CharacterInterface = Cast<ICCharacterInterface>(OwnerCharacter);
	CheckNull(CharacterInterface);
	CharacterInterface->SetBodyColor(Color);
}

void ACEquipment::UnEquip_Implementation()
{
	OnEquipmentDelegate.Broadcast();
}

void ACEquipment::Begin_Equip_Implementation()
{
	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}

void ACEquipment::End_Equip_Implementation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
}

#include "CAnimNotifyState_Equip.h"
#include "Global.h"
#include "Actions/CEquipment.h"
#include "Actions/CActionData.h"
#include "Actions/CActionObject.h"
#include "Components/CActionComponent.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	CheckNull(MeshComp->GetOwner());
	
	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCActionObject* ActionData = ActionComp->GetCurrentDataObject();
	CheckNull(ActionData);
		
	ACEquipment* Equipment = ActionData->GetEquipment();
	CheckNull(Equipment);
	
	Equipment->Begin_Equip();
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCActionObject* ActionData = ActionComp->GetCurrentDataObject();
	CheckNull(ActionData);

	ACEquipment* Equipment = ActionData->GetEquipment();
	CheckNull(Equipment);

	Equipment->End_Equip();
}

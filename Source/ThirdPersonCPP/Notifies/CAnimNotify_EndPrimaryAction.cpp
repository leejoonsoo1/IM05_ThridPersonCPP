#include "CAnimNotify_EndPrimaryAction.h"
#include "Global.h"
#include "Components/CActionComponent.h"
#include "Actions/CActionData.h"
#include "Actions/CActionObject.h"
#include "Actions/CDoAction.h"

FString UCAnimNotify_EndPrimaryAction::GetNotifyName_Implementation() const
{
	return "EndAction";
}

void UCAnimNotify_EndPrimaryAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	CheckNull(MeshComp->GetOwner());

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
	CheckNull(ActionComp);

	UCActionObject* ActionData = ActionComp->GetCurrentDataObject();
	CheckNull(ActionData);

	ACDoAction* DoAction = ActionData->GetDoAction();
	CheckNull(DoAction);

	DoAction->End_PrimaryAction();
}

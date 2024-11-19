#include "CAnimNotifyState_Combo.h"
#include "Global.h"
#include "Actions/CDoAction_Melee.h"
#include "Actions/CActionData.h"
#include "Components/CActionComponent.h"

FString UCAnimNotifyState_Combo::GetNotifyName_Implementation() const
{
    return "Combo";
}

void UCAnimNotifyState_Combo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);
    CheckNull(MeshComp->GetOwner());

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);

    UCActionData* ActionData = ActionComp->GetCurrentDataAsset();
    CheckNull(ActionData);

    ACDoAction* DoAction = ActionData->GetDoAction();
    CheckNull(DoAction);

    ACDoAction_Melee* Melee = Cast<ACDoAction_Melee>(DoAction);
    CheckNull(Melee);

    Melee->EnableCombo();
}

void UCAnimNotifyState_Combo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::NotifyEnd(MeshComp, Animation);
    CheckNull(MeshComp->GetOwner());

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);

    UCActionData* ActionData = ActionComp->GetCurrentDataAsset();
    CheckNull(ActionData);

    ACDoAction* DoAction = ActionData->GetDoAction();
    CheckNull(DoAction);

    ACDoAction_Melee* Melee = Cast<ACDoAction_Melee>(DoAction);
    CheckNull(Melee);

    Melee->DisableCombo();
}
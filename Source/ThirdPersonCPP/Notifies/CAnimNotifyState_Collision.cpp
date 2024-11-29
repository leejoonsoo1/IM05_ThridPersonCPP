#include "CAnimNotifyState_Collision.h"
#include "Actions/CAttachment.h"
#include "Actions/CActionData.h"
#include "Actions/CActionObject.h"
#include "Actions/CDoAction_Melee.h"
#include "Components/CActionComponent.h"
#include "Global.h"

FString UCAnimNotifyState_Collision::GetNotifyName_Implementation() const
{
    return "Collision";
}

void UCAnimNotifyState_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration);
    CheckNull(MeshComp->GetOwner());

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);

    UCActionObject* ActionData = ActionComp->GetCurrentDataObject();
    CheckNull(ActionData);

    ACAttachment* Attachment = ActionData->GetAttachment();
    CheckNull(Attachment);

    CLog::Log("UCAnimNotifyState_Collision::NotifyBegin");

    Attachment->OnCollision();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::NotifyEnd(MeshComp, Animation);
    CheckNull(MeshComp->GetOwner());

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);

    UCActionObject* ActionData = ActionComp->GetCurrentDataObject();
    CheckNull(ActionData);

    ACAttachment* Attachment = ActionData->GetAttachment();
    CheckNull(Attachment);

    Attachment->OffCollision();

    ACDoAction_Melee* Melee = Cast<ACDoAction_Melee>(ActionData->GetDoAction());
    CheckNull(Melee);

    Melee->ClearHittedCharacters();
}
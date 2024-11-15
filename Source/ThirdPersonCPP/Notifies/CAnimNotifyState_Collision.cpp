#include "CAnimNotifyState_Collision.h"
#include "Actions/CAttachment.h"
#include "Actions/CActionData.h"
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

    UCActionData* ActionData = ActionComp->GetCurrentDataAsset();
    CheckNull(ActionData);

    ACAttachment* Attachment = ActionData->GetAttachment();
    CheckNull(Attachment);

    CLog::Log("UCAnimNotifyState_Collision::NotifyBegi");

    Attachment->OnCollision();
}

void UCAnimNotifyState_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::NotifyEnd(MeshComp, Animation);
    CheckNull(MeshComp->GetOwner());

    UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(MeshComp->GetOwner());
    CheckNull(ActionComp);

    UCActionData* ActionData = ActionComp->GetCurrentDataAsset();
    CheckNull(ActionData);

    ACAttachment* Attachment = ActionData->GetAttachment();
    CheckNull(Attachment);

    Attachment->OffCollision();
}


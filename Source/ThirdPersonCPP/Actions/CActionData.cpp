#include "CActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter)
{
	FTransform TM;

	if (AttachmentClass)
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass, TM, InOwnerCharacter);
		Attachment->SetActorLabel(MakeLabel(InOwnerCharacter, "Attachment"));
		Attachment->FinishSpawning(TM);
	}
	
	if (EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass, TM, InOwnerCharacter);
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(MakeLabel(InOwnerCharacter, "Equipment"));
		Equipment->FinishSpawning(TM);

		if (Attachment)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment,	&ACAttachment::OnEquip);
			Equipment->OnUnEquipmentDelegate.AddDynamic(Attachment, &ACAttachment::OnUnEquip);
		}
	}

	if (DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass, TM, InOwnerCharacter);
		DoAction->SetDatas(DoActionDatas);
		DoAction->SetActorLabel(MakeLabel(InOwnerCharacter, "DoAction"));
		DoAction->FinishSpawning(TM);

		if (Equipment)
		{
			DoAction->SetEquipped(Equipment->IsEquipped());
		}

		if (Attachment)
		{
			Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction,	&ACDoAction::OnAttachmentBeginOverlap);
			Attachment->OnAttachmentEndOverlap.AddDynamic(DoAction,		&ACDoAction::OnAttachmentEndOverlap);
		}
	}
}

FString UCActionData::MakeLabel(ACharacter* InOwnerCharacter, FString InMiddleName)
{
	FString Label;
	Label.Append(InOwnerCharacter->GetActorLabel());
	Label.Append("_");
	Label.Append(InMiddleName);
	Label.Append(GetName().Replace(TEXT("DA_"), TEXT(""))); // DA_Unarmed

	return Label;
}

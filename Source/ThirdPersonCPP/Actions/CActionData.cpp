#include "CActionData.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "CEquipment.h"
#include "CAttachment.h"
#include "CDoAction.h"
#include "CActionObject.h"

void UCActionData::BeginPlay(ACharacter* InOwnerCharacter, UCActionObject** OutActionObject)
{
	FTransform TM;

	ACAttachment* Attachment = nullptr;
	if (AttachmentClass)
	{
		Attachment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACAttachment>(AttachmentClass,	TM, InOwnerCharacter);
		Attachment->SetActorLabel(MakeLabel(InOwnerCharacter,	"Attachment"));
		Attachment->FinishSpawning(TM);
	}
	
	ACEquipment* Equipment = nullptr;
	if (EquipmentClass)
	{
		Equipment = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACEquipment>(EquipmentClass,		TM, InOwnerCharacter);
		Equipment->SetData(EquipmentData);
		Equipment->SetColor(EquipmentColor);
		Equipment->SetActorLabel(MakeLabel(InOwnerCharacter,	"Equipment"));
		Equipment->FinishSpawning(TM);

		if (Attachment)
		{
			Equipment->OnEquipmentDelegate.AddDynamic(Attachment,		&ACAttachment::OnEquip);
			Equipment->OnUnEquipmentDelegate.AddDynamic(Attachment,		&ACAttachment::OnUnEquip);
		}
	}

	ACDoAction* DoAction = nullptr;
	if (DoActionClass)
	{
		DoAction = InOwnerCharacter->GetWorld()->SpawnActorDeferred<ACDoAction>(DoActionClass,			TM, InOwnerCharacter);
		DoAction->SetDatas(DoActionDatas);
		DoAction->SetActorLabel(MakeLabel(InOwnerCharacter,		"DoAction"));
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

	*OutActionObject = NewObject<UCActionObject>();
	(*OutActionObject)->Attachment		= Attachment;
	(*OutActionObject)->Equipment		= Equipment;
	(*OutActionObject)->DoAction		= DoAction;
	(*OutActionObject)->EquipmentColor	= EquipmentColor;
}

//

FString UCActionData::MakeLabel(ACharacter* InOwnerCharacter, FString InMiddleName)
{
	FString Label;
	Label.Append(InOwnerCharacter->GetActorLabel());
	Label.Append("_");
	Label.Append(InMiddleName);
	Label.Append(GetName().Replace(TEXT("DA_"), TEXT(""))); // DA_Unarmed

	return Label;
}

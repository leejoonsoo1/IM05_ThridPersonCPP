#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"

void ACDoAction_Melee::PrimaryAction()
{
	Super::PrimaryAction();

	CheckFalse(Datas.Num() > 0);
	CheckFalse(StateComp->IsIdleMode());


	StateComp->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].Montage, Datas[0].PlayRate, Datas[0].StartSection);

	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}


void ACDoAction_Melee::Begin_PrimaryAction()
{
	Super::Begin_PrimaryAction();
}

void ACDoAction_Melee::End_PrimaryAction()
{
	Super::End_PrimaryAction();

	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	FDamageEvent Damage;
	InOtherCharacter->TakeDamage(Datas[ComboCount].Damage, Damage, InAttacker->GetController(), InCauser);
}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InCauser, InOtherCharacter)
}


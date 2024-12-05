#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"

void ACDoAction_Melee::PrimaryAction()
{
	Super::PrimaryAction();
	CheckFalse(Datas.Num() > 0);

	// CanAttack
	if (!bCanAttack)
	{
		return;
	}

	// Combo Attack
	if (bCanCombo)
	{
		bCanCombo = false;
		bSuccessCombo = true;

		return;	
	}

	// First Attack
	CheckFalse(StateComp->IsIdleMode());
	StateComp->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].Montage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}


void ACDoAction_Melee::Begin_PrimaryAction()
{
	Super::Begin_PrimaryAction();

	CheckFalse(bSuccessCombo);
	bSuccessCombo = false;

	OwnerCharacter->StopAnimMontage();

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);
	
	OwnerCharacter->PlayAnimMontage(Datas[ComboCount].Montage, Datas[ComboCount].PlayRate, Datas[ComboCount].StartSection);
	Datas[ComboCount].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}

void ACDoAction_Melee::End_PrimaryAction()
{
	Super::End_PrimaryAction();

	OwnerCharacter->StopAnimMontage(Datas[ComboCount].Montage);
	ComboCount = 0;

	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	// Check Multiple Hit
	int32 PrevHitted = HittedCharacters.Num();
	HittedCharacters.AddUnique(InOtherCharacter);
	CheckFalse(PrevHitted < HittedCharacters.Num());

	// Hit Stop
	float HitStop = Datas[ComboCount].HitStop;
	if (!FMath::IsNearlyZero(HitStop))
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 2e-2f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreGlobalTimeDelation", HitStop * 2e-2f, false);
	}

	// Spawn Impact Effect
	UParticleSystem* ImpactEffect = Datas[ComboCount].Effect;

	if (ImpactEffect)
	{
		FTransform TM = Datas[ComboCount].EffectTransform;
		TM.AddToTranslation(InOtherCharacter->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, TM);
	}

	// Play CameraShake
	TSubclassOf<UCameraShake> ShakeClass = Datas[ComboCount].ShakeClass;
	if (ShakeClass)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PC->PlayerCameraManager->PlayCameraShake(ShakeClass);

	}

	CLog::Log("ACDoAction_Melee::OnAttachmentBeginOverlap");

	FDamageEvent DamageEvent;
	InOtherCharacter->TakeDamage(Datas[ComboCount].Damage, DamageEvent, InAttacker->GetController(), InCauser);
}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InCauser, InOtherCharacter);
}

void ACDoAction_Melee::EnableCombo()
{
	bCanCombo = true;
}

void ACDoAction_Melee::DisableCombo()
{
	
	bCanCombo = false;
}

void ACDoAction_Melee::ClearHittedCharacters()
{
	HittedCharacters.Empty();
}

void ACDoAction_Melee::RestoreGlobalTimeDelation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
}

void ACDoAction_Melee::FlipFlop()
{
}

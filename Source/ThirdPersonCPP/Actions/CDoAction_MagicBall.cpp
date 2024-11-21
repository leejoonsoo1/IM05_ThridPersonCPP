#include "CDoAction_MagicBall.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"
#include "CAim.h"

void ACDoAction_MagicBall::BeginPlay()
{
	Super::BeginPlay();

	// Constructor	: CreateDefaultSubObject<T>
	// PlayTime		: NewObject<T>

	Aim = NewObject<UCAim>();
}

void ACDoAction_MagicBall::Tick(float DelatTime)
{
	Super::Tick(DelatTime);
}

void ACDoAction_MagicBall::PrimaryAction()
{
	Super::PrimaryAction();
	CheckFalse(Datas.Num() > 0);
	CheckFalse(StateComp->IsIdleMode());
	
	StateComp->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].Montage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}

void ACDoAction_MagicBall::Begin_PrimaryAction()
{
	// Spawn Projectile
}

void ACDoAction_MagicBall::End_PrimaryAction()
{
	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}
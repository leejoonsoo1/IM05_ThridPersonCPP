#include "CDoAction_MagicBall.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"
#include "CAim.h"
#include "CProjectile.h"

void ACDoAction_MagicBall::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();
	Aim->Initialize(OwnerCharacter);

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(OwnerCharacter);
	if (ActionComp)
	{
		ActionComp->OnActionTypeChanged.AddDynamic(this, &ACDoAction_MagicBall::OnActionTypeChanged);
	}
}

void ACDoAction_MagicBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Aim->Tick(DeltaTime);
}

void ACDoAction_MagicBall::PrimaryAction()
{
	Super::PrimaryAction();

	CheckFalse(Datas.Num() > 0);
	CheckFalse(StateComp->IsIdleMode());
	
	if (Aim->IsAvaliable())
	{
		CheckFalse(Aim->IsZooming());
	}

	StateComp->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].Montage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}

void ACDoAction_MagicBall::Begin_PrimaryAction()
{
	Super::Begin_PrimaryAction();

	CheckNull(Datas[0].ProjectileClass);

	FVector CamLoc;
	FRotator CamRot;
	OwnerCharacter->GetController()->GetPlayerViewPoint(CamLoc, CamRot);

	FVector HandLocation = OwnerCharacter->GetMesh()->GetSocketLocation("hand_r");

	FVector SpawnLocation = CamLoc + CamRot.Vector() * ((HandLocation - CamLoc) | CamRot.Vector());

	FTransform TM;
	TM.SetLocation(SpawnLocation);
	TM.SetRotation(FQuat(CamRot));

	ACProjectile* ProjectileObject = GetWorld()->SpawnActorDeferred<ACProjectile>
	(
		Datas[0].ProjectileClass,
		TM,
		OwnerCharacter,
		OwnerCharacter,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	ProjectileObject->OnProjectileBeginOverlap.AddDynamic(this, &ACDoAction_MagicBall::OnProjectileBeginOverlap);

	ProjectileObject->FinishSpawning(TM);

}

void ACDoAction_MagicBall::End_PrimaryAction()
{
	Super::End_PrimaryAction();

	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}

void ACDoAction_MagicBall::Begin_SecondaryAction()
{
	CheckNull(Aim);

	Aim->On();
}

void ACDoAction_MagicBall::End_SecondaryAction()
{
	CheckNull(Aim);

	Aim->Off();
}

void ACDoAction_MagicBall::OnProjectileBeginOverlap(const FHitResult& InHitResult)
{
	//Spawn Impact Effect
	UParticleSystem* ImpactEffect = Datas[0].Effect;
	if (ImpactEffect)
	{
		FTransform TM = Datas[0].EffectTransfrom;
		TM.AddToTranslation(InHitResult.ImpactPoint);
		TM.SetRotation(FQuat(InHitResult.ImpactNormal.Rotation()));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, TM);
	}

	//Play CameraShake
	TSubclassOf<UCameraShake> ShakeClass = Datas[0].ShakeClass;
	if (ShakeClass)
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

		if (PC)
		{
			PC->PlayerCameraManager->PlayCameraShake(ShakeClass);
		}
	}

	//Take Damage
	FDamageEvent DamageEvent;
	InHitResult.GetActor()->TakeDamage(Datas[0].Damage, DamageEvent, OwnerCharacter->GetController(), this);
}


void ACDoAction_MagicBall::OnActionTypeChanged(EActionType InPrevType, EActionType InNewType)
{
	CheckFalse(Aim->IsAvaliable());
	CheckFalse(Aim->IsZooming());
	
	Aim->Off();
}
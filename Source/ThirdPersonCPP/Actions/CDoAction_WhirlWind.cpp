#include "CDoAction_WhirlWind.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"
#include "Particles\ParticleSystemComponent.h"
#include "CAttachment.h"

ACDoAction_WhirlWind::ACDoAction_WhirlWind()
{
	DamageToTime	= 0.1;
	ActiveTime		= 5.f;
	AroundSpeed		= 200.f;
	Radius			= 300.f;
}

void ACDoAction_WhirlWind::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Child : OwnerCharacter->Children)
	{
		if (Child->IsA<ACAttachment>() && Child->GetActorLabel().Contains("WhirlWind"))
		{
			BoxComp = CHelpers::GetComponent<UBoxComponent>(Child);

			break;
		}
	}

	CheckNull(BoxComp);
	ACAttachment* Attachment = Cast<ACAttachment>(BoxComp->GetOwner());
	CheckNull(Attachment);

	Attachment->OffCollision();
}

void ACDoAction_WhirlWind::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Center = OwnerCharacter->GetActorLocation();
	CurrentYaw += DeltaTime * AroundSpeed;
	CurrentYaw = FMath::Fmod(CurrentYaw, 360.f);

	FVector FromAway = FVector(Radius, 0, 0);
	FVector CollisionLocation = FromAway.RotateAngleAxis(CurrentYaw, FVector::UpVector);

	Center += CollisionLocation;
	BoxComp->SetWorldLocation(Center);
}

void ACDoAction_WhirlWind::PrimaryAction()
{
	Super::PrimaryAction();

	CheckFalse(Datas.Num() > 0);
	CheckFalse(StateComp->IsIdleMode());

	CheckTrue(bActivation);

	StateComp->SetActionMode();
	bActivation = true;

	OwnerCharacter->PlayAnimMontage(Datas[0].Montage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();
}

void ACDoAction_WhirlWind::Begin_PrimaryAction()
{
	Super::Begin_PrimaryAction();

	CurrentYaw = OwnerCharacter->GetActorForwardVector().Rotation().Yaw;

	// Attach FX
	if (BoxComp && Datas.Num() && Datas[0].Effect)
	{
		EffectComp = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, BoxComp, NAME_None);
		EffectComp->SetRelativeTransform(Datas[0].EffectTransform);		
	}

	// On Collision
	ACAttachment* Attachment = Cast<ACAttachment>(BoxComp->GetOwner());
	CheckNull(Attachment);

	Attachment->OnCollision();

	// TickDamage Timer
	UKismetSystemLibrary::K2_SetTimer(this, "TickDamage", DamageToTime, true);
}

void ACDoAction_WhirlWind::End_PrimaryAction()
{
	Super::End_PrimaryAction();

	StateComp->SetIdleMode();
	AttributeComp->SetMove();

	// DeActivate Timer
	FTimerDynamicDelegate DeActivateDelegate;
	DeActivateDelegate.BindUFunction(this, "DeActivate");
	UKismetSystemLibrary::K2_SetTimerDelegate(DeActivateDelegate, ActiveTime, false);
}

void ACDoAction_WhirlWind::Abort()
{
	Super::Abort();

	DeActivate();
}

void ACDoAction_WhirlWind::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	HittedCharacters.AddUnique(InOtherCharacter);
}

void ACDoAction_WhirlWind::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InCauser, InOtherCharacter);

	HittedCharacters.Remove(InOtherCharacter);
}

void ACDoAction_WhirlWind::TickDamage()
{
	CheckFalse(Datas.Num() > 0);
	
	FDamageEvent DamageEvent;

	for (int32 i = 0; i < HittedCharacters.Num(); i++)
	{
		UCStateComponent* OtherStateComp = nullptr;

		if (HittedCharacters[i])
		{
			OtherStateComp = CHelpers::GetComponent<UCStateComponent>(HittedCharacters[i]);
		}

		bool bIgnore = false;
		bIgnore |= (OtherStateComp == nullptr);
		bIgnore |= (OtherStateComp->IsDeadMode());
		bIgnore |= (HittedCharacters[i]->IsPendingKill());
		bIgnore |= (HittedCharacters[i] == nullptr);

		if (bIgnore)
		{
			continue;
		}

		HittedCharacters[i]->TakeDamage(Datas[0].Damage, DamageEvent, OwnerCharacter->GetController(), this);
	}
}

void ACDoAction_WhirlWind::DeActivate()
{
	bActivation = false;
	
	if (EffectComp)
	{
		EffectComp->DestroyComponent();
	}

	ACAttachment* Attachment = Cast<ACAttachment>(BoxComp->GetOwner());
	if (Attachment)
	{
		Attachment->OffCollision();
	}

	UKismetSystemLibrary::K2_ClearTimer(this, "TickDamage");
}

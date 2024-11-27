#include "CDoAction_WhirlWind.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"
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
}

void ACDoAction_WhirlWind::End_PrimaryAction()
{
	Super::End_PrimaryAction();

	StateComp->SetIdleMode();
	AttributeComp->SetMove();
}

void ACDoAction_WhirlWind::Abort()
{
	Super::Abort();
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

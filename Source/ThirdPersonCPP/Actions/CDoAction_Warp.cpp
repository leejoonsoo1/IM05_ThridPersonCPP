#include "CDoAction_Warp.h"
#include "Global.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CAttributeComponent.h"
#include "Components/CBehaviorComponent.h"
#include "CAttachment.h"

void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();

	for (const auto& Child : OwnerCharacter->Children)
	{
		if (Child->IsA<ACAttachment>() && Child->GetActorLabel().Contains("Warp"))
		{
			PreviewMeshComp = CHelpers::GetComponent<USkeletalMeshComponent>(Child);

			break;
		}
	}
}

void ACDoAction_Warp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PreviewMeshComp->SetVisibility(false);

	CheckFalse(*bEquipped);
	CheckFalse(IsOwnerPlayer());

	FVector CursorLocationToWorld;
	if (GetCursorLocation(CursorLocationToWorld))
	{
		PreviewMeshComp->SetVisibility(true);
		PreviewMeshComp->SetWorldLocation(CursorLocationToWorld);
	}
}

void ACDoAction_Warp::PrimaryAction()
{
	Super::PrimaryAction();

	CheckFalse(Datas.Num() > 0);
	CheckFalse(StateComp->IsIdleMode());
	
	if (IsOwnerPlayer())
	{
		CheckFalse(GetCursorLocation(LocationToWarp));
	}
	else
	{
		AController* AIC = OwnerCharacter->GetController();
		
		if (AIC)
		{
			UCBehaviorComponent* BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(AIC);

			if (BehaviorComp)
			{
				LocationToWarp = BehaviorComp->GetLocationValue();
			}
		}
	}

	StateComp->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].Montage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? AttributeComp->SetMove() : AttributeComp->SetStop();

	SetPreviewMeshColor(FLinearColor::Red);
}

void ACDoAction_Warp::Begin_PrimaryAction()
{
	Super::Begin_PrimaryAction();

	UParticleSystem* Effect = Datas[0].Effect;

	if (Effect)
	{
		/*
			FTransform TM = Datas[0].EffectTransform;
			TM.AddToTranslation(OwnerCharacter->GetMesh()->GetSocketLocation("Hand_ThrowItem"));
		*/

		UGameplayStatics::SpawnEmitterAttached(Effect, OwnerCharacter->GetMesh(), "Hand_ThrowItem", Datas[0].EffectTransform.GetLocation(), FRotator(Datas[0].EffectTransform.GetRotation()), Datas[0].EffectTransform.GetScale3D());
	}
}

void ACDoAction_Warp::End_PrimaryAction()
{
	Super::End_PrimaryAction();

	LocationToWarp.Z += OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	OwnerCharacter->SetActorLocation(LocationToWarp);

	StateComp->SetIdleMode();
	AttributeComp->SetMove();

	SetPreviewMeshColor(FLinearColor(0, 1, 1));
}

bool ACDoAction_Warp::GetCursorLocation(FVector& OutLocation)
{
	APlayerController* PC = OwnerCharacter->GetController<APlayerController>();
	//CheckNull(PC);	

	// Use C++ and BluePrint
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(ObjectTypeQuery1);
	
	FHitResult Hit;
	if (PC->GetHitResultUnderCursorForObjects(ObjectTypes, true, Hit))
	{
		OutLocation = Hit.Location;

		return true;
	}

	return false;
}

void ACDoAction_Warp::SetPreviewMeshColor(FLinearColor InColor)
{
	FVector Emissive = FVector(InColor.R, InColor.G, InColor.B);
	PreviewMeshComp->SetVectorParameterValueOnMaterials("Emissive", Emissive);
}

bool ACDoAction_Warp::IsOwnerPlayer()
{
	return OwnerCharacter->GetClass() == GetWorld()->GetAuthGameMode()->DefaultPawnClass;
}
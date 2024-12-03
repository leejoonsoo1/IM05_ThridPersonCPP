#include "CEnemy.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CAttributeComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UI/CNameWidget.h"
#include "UI/CHealthWidget.h"
#include "Actions/CActionData.h"

ACEnemy::ACEnemy()
{
	// Enable Tick;
	PrimaryActorTick.bCanEverTick = true;

	// MeshComp
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset, "/Game/Character/Mesh/SK_Mannequin");
	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UAnimInstance> AnimClass;
	CHelpers::GetClass(&AnimClass, "/Game/Enemies/ABP_CEnemy");
	GetMesh()->SetAnimInstanceClass(AnimClass);

	// Action Comp
	CHelpers::CreateActorComponent(this, &ActionComp,		"ActionComp");

	// Montages Comp
	CHelpers::CreateActorComponent(this, &MontagesComp,		"MontagesComp");

	// AttributeComp
	CHelpers::CreateActorComponent(this, &AttributeComp,	"AttributeComp");

	// State Comp
	CHelpers::CreateActorComponent(this, &StateComp,		"StateComp");

	// Widget Comp
	CHelpers::CreateSceneComponent(this, &NameWidgetComp,	"NameWidgetComp",	GetMesh());
	CHelpers::CreateSceneComponent(this, &HealthWidgetComp, "HealthWidgetComp", GetMesh());

	// NameWidget Class
	TSubclassOf<UCNameWidget> NameWidgetClass;
	CHelpers::GetClass(&NameWidgetClass, "/Game/UI/WB_Name");
	NameWidgetComp->SetWidgetClass(NameWidgetClass);
	NameWidgetComp->SetRelativeLocation(FVector(0, 0, 240));
	NameWidgetComp->SetDrawSize(FVector2D(240, 30));
	NameWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);

	// HealthWidget Class
	TSubclassOf<UCHealthWidget> HealthWidgetClass;
	CHelpers::GetClass(&HealthWidgetClass, "/Game/UI/WB_Health");
	HealthWidgetComp->SetWidgetClass(HealthWidgetClass);
	HealthWidgetComp->SetRelativeLocation(FVector(0, 0, 190));
	HealthWidgetComp->SetDrawSize(FVector2D(120, 20));
	HealthWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);

	// MovementComp
	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetSprintSpeed();
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	// Get Dissolve Curve Asset
	CHelpers::GetAsset(&DissolveCurve, "/Game/Curves/Curve_Dissolve");

	LaunchValue = 30.f;
}

void ACEnemy::BeginPlay()
{
	// Set Dynamic Material
	BodyMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	// BluePrint BeingPlay
	Super::BeginPlay();

	//On StateType Changed
	StateComp->OnStateTypeChanged.AddDynamic(this, &ACEnemy::OnStateTypeChanged);
	//ActionComp->SetUnarmedMode();

	// Widget Settings
	NameWidgetComp->InitWidget();
	UCNameWidget* NameWidgetObject = Cast<UCNameWidget>(NameWidgetComp->GetUserWidgetObject());
	if (NameWidgetObject)
	{
		FString ControllerName	= GetController()->GetName();
		FString PawnName		= GetName();

		NameWidgetObject->SetNameText(ControllerName, PawnName);
	}

	// Health Settings
	HealthWidgetComp->InitWidget();
	UCHealthWidget* HealthWidgetObject = Cast<UCHealthWidget>(HealthWidgetComp->GetUserWidgetObject());
	if (HealthWidgetObject)
	{
		float MaxHealth		= AttributeComp->GetMaxHealth();
		float CurrentHealth = AttributeComp->GetCurrentHealth();

		HealthWidgetObject->Update(CurrentHealth, MaxHealth);
	}

	// Get Dissovle Material
	UMaterialInstanceConstant* DissolveMaterialAsset;
	CHelpers::GetAssetDynamic(&DissolveMaterialAsset, "/Game/Materials/MI_Dissolve");
	DissolveMaterial = UMaterialInstanceDynamic::Create(DissolveMaterialAsset, nullptr);

	// Bind Dissolve Timeline Event
	FOnTimelineFloat DissolveTimelineDelegate;
	DissolveTimelineDelegate.BindUFunction(this, "OnProgressDissolve");
	DissolveTimeline.AddInterpFloat(DissolveCurve, DissolveTimelineDelegate);

	FOnTimelineEvent DissolveTimelineFinish;
	DissolveTimelineFinish.BindUFunction(this, "OnFinishDissolve");
	DissolveTimeline.SetTimelineFinishedFunc(DissolveTimelineFinish);
}

void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DissolveTimeline.TickTimeline(DeltaTime);
}

float ACEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage	= Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	DamageInstigator	= EventInstigator;
	DamageValue			= ActualDamage;

	AttributeComp->DecreaseHealth(Damage);

	if (AttributeComp->GetCurrentHealth() <= 0.f)
	{
		StateComp->SetDeadMode();
		
		return ActualDamage;
	}

	StateComp->SetHittedMode();

	return ActualDamage;
}

void ACEnemy::SetBodyColor(FLinearColor InColor)
{
	CheckTrue(StateComp->IsDeadMode());

	if (StateComp->IsHittedMode())
	{
		LogoMaterial->SetScalarParameterValue("bHitted", 1.f);
		LogoMaterial->SetScalarParameterValue("BodyColor", 1.f);

		return;
	}

	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

void ACEnemy::Hitted()
{
	// Update Health Widget
	UCHealthWidget* HealthWidgetObject = Cast<UCHealthWidget>(HealthWidgetComp->GetUserWidgetObject());

	if (HealthWidgetObject)
	{
		HealthWidgetObject->Update(AttributeComp->GetCurrentHealth(), AttributeComp->GetMaxHealth());
	}

	// Play Hitted Montages
	MontagesComp->PlayHitted();

	// Hit Back
	FVector Start			= DamageInstigator->GetPawn()->GetActorLocation();
	FVector Target			= GetActorLocation();
	FVector LaunchDirection = (Target - Start).GetSafeNormal();
	
	LaunchCharacter(LaunchDirection * DamageValue * LaunchValue, true, false);

	// Change Logo Color
	SetBodyColor(FLinearColor::Red * 100.f);
	UKismetSystemLibrary::K2_SetTimer(this, "ResotreBodyColor", 0.5f, false);
}

void ACEnemy::Dead()
{
	// Hidden Widgets
	NameWidgetComp->SetVisibility(false);
	HealthWidgetComp->SetVisibility(false);

	// Ragdoll
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();

	// Add Impluse
	FVector Start		= GetActorLocation();
	FVector Target		= DamageInstigator->GetPawn()->GetActorLocation();
	FVector Direction	= (Start - Target);
	Direction.Normalize();
	GetMesh()->AddImpulseAtLocation(Direction * DamageValue * 3000.f, Start);

	// Start Dissolve Timeline
	FLinearColor EquipmentColor = FLinearColor::White;
	if (ActionComp->GetCurrentDataAsset())
	{
		EquipmentColor = ActionComp->GetCurrentDataAsset()->EquipmentColor;
	}

	DissolveMaterial->SetVectorParameterValue("BaseColor", EquipmentColor);

	for (int i = 0; i < GetMesh()->GetNumMaterials(); i++)
	{
		GetMesh()->SetMaterial(i, DissolveMaterial);
	}
	
	// Off All Attachment Collision
	ActionComp->OffAllCollisions();

	//Start Disosolve Timeline
	DissolveTimeline.PlayFromStart();
}

void ACEnemy::ResotreBodyColor()
{
	LogoMaterial->SetScalarParameterValue("bHitted", 0.f);

	if (ActionComp->GetCurrentDataAsset())
	{
		FLinearColor EquipmentColor = ActionComp->GetCurrentDataAsset()->EquipmentColor;

		LogoMaterial->SetVectorParameterValue("BodyColor", EquipmentColor);
	}
}

void ACEnemy::OnProgressDissolve(float Output)
{
	CheckNull(DissolveMaterial);
	DissolveMaterial->SetScalarParameterValue("Amount", Output);
}

void ACEnemy::OnFinishDissolve()
{
	// Destroy All Spawned Equipment, Attachment, DoAction
	ActionComp->DestroyAll();

	Destroy();
}

void ACEnemy::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Hitted:
		{
			Hitted();
		}
		break;

		case EStateType::Dead:
		{
			Dead();
		}
		break;
	}
}

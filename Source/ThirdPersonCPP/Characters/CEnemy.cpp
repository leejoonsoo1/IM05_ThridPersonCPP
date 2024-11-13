#include "CEnemy.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CAttributeComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UI/CNameWidget.h"
#include "UI/CHealthWidget.h"

ACEnemy::ACEnemy()
{
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
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//bUseControllerRotationYaw = false;
}

void ACEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Set Dynamic Material
	BodyMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	// On StateType Changed
	ActionComp->SetUnarmedMode();

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
}

void ACEnemy::SetBodyColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}
#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/CAttributeComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CFeetComponent.h"
#include "Actions/CActionData.h"
#include "Assignment/CChest.h"
#include "Assignment/CDoor.h"
#include "Blueprint/UserWidget.h"
#include "Assignment/CWidget.h"
#include "Math\UnrealMathUtility.h"

ACPlayer::ACPlayer()
{
	// SpringArm
	CHelpers::CreateSceneComponent(this, &SpringArmComp, "SpringArmComp", GetMesh());
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 140));
	SpringArmComp->AddRelativeRotation(FRotator(0, 90, 0));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = true;

	// CameraComp
	CHelpers::CreateSceneComponent(this, &CameraComp, "CameraComp", SpringArmComp);

	// MeshComp
	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset(&MeshAsset,							"/Game/Character/Mesh/SK_Mannequin");
	GetMesh()->SetSkeletalMesh(MeshAsset);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	TSubclassOf<UAnimInstance> AnimClass;
	CHelpers::GetClass(&AnimClass,							"/Game/Player/ABP_CPlayer");
	GetMesh()->SetAnimInstanceClass(AnimClass);
	
	// Action Comp
	CHelpers::CreateActorComponent(this, &ActionComp,		"ActionComp");

	// Montages Comp
	CHelpers::CreateActorComponent(this, &MontagesComp,		"MontagesComp");

	// AttributeComp
	CHelpers::CreateActorComponent(this, &AttributeComp,	"AttributeComp");

	// OptionComp
	CHelpers::CreateActorComponent(this, &OptionComp,		"OptionComp");

	// State Comp
	CHelpers::CreateActorComponent(this, &StateComp,		"StateComp");
	
	// Feet Comp
	CHelpers::CreateActorComponent(this, &FeetComp,			"FeetComp");

	// MovementComp
	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetSprintSpeed();
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;

	CHelpers::GetClass(&KeyWidgetClass, "/Game/UI/WB_HasKeys");

	// PostProcess Comp
	CHelpers::CreateSceneComponent<UPostProcessComponent>(this, &PostProcessComp, "PostProcessComp", GetRootComponent());
	PostProcessComp->bEnabled = false;

	// Property Settings
	TeamID = 0;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (KeyWidgetClass)
	{
		KeyWidget = CreateWidget<UCWidget>(GetController<APlayerController>(), KeyWidgetClass);
		KeyWidget->AddToViewport();
		KeyWidget->SetVisibility(ESlateVisibility::Visible);
	}

	// Set Dynamic Material
	BodyMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), nullptr);
	
	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	//On StateType Changed
	StateComp->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);
	ActionComp->SetUnarmedMode();
}

void ACPlayer::SetBodyColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(TeamID);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",							this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight",								this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn",									this, &ACPlayer::OnTurn);
	PlayerInputComponent->BindAxis("LookUp",								this, &ACPlayer::OnLookUp);
	PlayerInputComponent->BindAxis("Zoom",									this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Evade",				IE_Pressed,		this, &ACPlayer::OnEvade);

  PlayerInputComponent->BindAction("Interact",	IE_Pressed,		this, &ACPlayer::Interact);
	PlayerInputComponent->BindAction("Walk",				IE_Pressed,		this, &ACPlayer::OnWalk);
	PlayerInputComponent->BindAction("Walk",				IE_Released,	this, &ACPlayer::OffWalk);

	PlayerInputComponent->BindAction("Fist",				IE_Pressed,		this, &ACPlayer::OnFist);
	PlayerInputComponent->BindAction("OneHand",				IE_Released,	this, &ACPlayer::OnOneHand);
	PlayerInputComponent->BindAction("TwoHand",				IE_Pressed,		this, &ACPlayer::OnTwoHand);
	PlayerInputComponent->BindAction("MagicBall",			IE_Released,	this, &ACPlayer::OnMagicBall);
	PlayerInputComponent->BindAction("Warp",				IE_Pressed,		this, &ACPlayer::OnWarp);
	PlayerInputComponent->BindAction("WhirlWind",			IE_Released,	this, &ACPlayer::OnWhirlWind);

	PlayerInputComponent->BindAction("PrimaryAction",		IE_Pressed,		this, &ACPlayer::OnPrimaryAction);
	PlayerInputComponent->BindAction("SecondaryAction",		IE_Pressed,		this, &ACPlayer::OnBeginSecondaryAction);
	PlayerInputComponent->BindAction("SecondaryAction",		IE_Released,	this, &ACPlayer::OnEndSecondaryAction);
}

float ACPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	DamageInstigator = EventInstigator;
	DamageValue = ActualDamage;

	ActionComp->Abort();

	AttributeComp->DecreaseHealth(Damage);

	if (AttributeComp->GetCurrentHealth() <= 0.f)
	{
		StateComp->SetDeadMode();

		return ActualDamage;
	}

	StateComp->SetHittedMode();

	return ActualDamage;
}

void ACPlayer::OnMoveForward(float Axis)
{
	CheckFalse(AttributeComp->IsCanMove());

	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetForwardVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	CheckFalse(AttributeComp->IsCanMove());

	FRotator ControlRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(ControlRot).GetRightVector();

	AddMovementInput(Direction, Axis);
}

void ACPlayer::OnTurn(float Axis)
{
	float Rate = Axis * OptionComp->GetMouseXSpeed()* GetWorld()->GetDeltaSeconds();

	AddControllerYawInput(Rate);
}

void ACPlayer::OnLookUp(float Axis)
{
	float Rate = Axis * OptionComp->GetMouseYSpeed() * GetWorld()->GetDeltaSeconds();

	AddControllerPitchInput(Rate);
}

void ACPlayer::OnZoom(float Axis)
{
	float Rate = OptionComp->GetZoomSpeed() * Axis * GetWorld()->GetDeltaSeconds();

	SpringArmComp->TargetArmLength	+=	Rate;
	SpringArmComp->TargetArmLength	=	FMath::Clamp(SpringArmComp->TargetArmLength, OptionComp->GetZoomMin(), OptionComp->GetZoomMax());
}

void ACPlayer::OnEvade()
{
	CheckFalse(StateComp->IsIdleMode());
	CheckFalse(AttributeComp->IsCanMove());

	// Only C++ Function.
	if (InputComponent->GetAxisValue("MoveForward") < 0)
	{
		StateComp->SetBackstepMode();

		return;
	}

	StateComp->SetRollMode();
}

void ACPlayer::OnWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetWalkSpeed();
}

void ACPlayer::OffWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetSprintSpeed();
}

void ACPlayer::OnFist()
{
	CheckFalse(StateComp->IsIdleMode());

	ActionComp->SetFistMode();
}

void ACPlayer::OnOneHand()
{
	CheckFalse(StateComp->IsIdleMode());

	ActionComp->SetOneHandMode();
}

void ACPlayer::OnTwoHand()
{
	CheckFalse(StateComp->IsIdleMode());

	ActionComp->SetTwoHandMode();
}

void ACPlayer::OnMagicBall()
{
	CheckFalse(StateComp->IsIdleMode());

	ActionComp->SetMagicBallMode();
}

void ACPlayer::OnWarp()
{
	CheckFalse(StateComp->IsIdleMode());

	ActionComp->SetWarpMode();
}

void ACPlayer::OnWhirlWind()
{
	CheckFalse(StateComp->IsIdleMode());
	
	ActionComp->SetWhirlWindMode();
}

void ACPlayer::Interact()
{
	FHitResult HitResult;
	FLinearColor KeyColor;
	FCollisionQueryParams Params;
	FVector Start	= GetActorLocation();
	FVector End		= Start + GetActorForwardVector() * 300;

	Params.AddIgnoredActor(this);;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_WorldDynamic, Params);
	
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		CheckNull(HitActor);

		if (HitActor->IsA(ACChest::StaticClass()))
		{
			ACChest* Chest = Cast<ACChest>(HitActor);
			CheckNull(Chest);
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 1.0f);

			KeyColor = Chest->GetSymbolColor();

			KeyColor.R = FMath::Clamp(KeyColor.R, 0.f, 1.f);
			KeyColor.G = FMath::Clamp(KeyColor.G, 0.f, 1.f);
			KeyColor.B = FMath::Clamp(KeyColor.B, 0.f, 1.f);

			KeyWidget->SetKey(KeyColor);
			RootKey(KeyColor);
			Chest->Interact();
		}
		else if (HitActor->IsA(ACDoor::StaticClass()))
		{
			ACDoor* Door = Cast<ACDoor>(HitActor);
			CheckNull(Door);
			DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 1.0f);

			FLinearColor DoorColor = Door->GetSymbolColor();

			DoorColor.R = FMath::Clamp(DoorColor.R, 0.f, 1.f);
			DoorColor.G	= FMath::Clamp(DoorColor.G, 0.f, 1.f);
			DoorColor.B	= FMath::Clamp(DoorColor.B, 0.f, 1.f);

			if (Key.Find(DoorColor))
			{
				Door->Interact();
			}
			else
			{
				FVector Location	= HitResult.ImpactPoint;
				FString DebugText	= TEXT("You don't have a key");
				FColor TextColor	= FColor::White;
				float Duration		= 3.f;
				bool bDrawShadow		= true;

				DrawDebugString(GetWorld(), Location, DebugText, nullptr, TextColor, Duration, bDrawShadow);
			}
		}
	}

void ACPlayer::OnPrimaryAction()
{
	CLog::Log("ACPlayer::OnPrimaryAction");
	ActionComp->PrimaryAction();
}

void ACPlayer::OnBeginSecondaryAction()
{
	ActionComp->Begin_SecondaryAction();
}

void ACPlayer::OnEndSecondaryAction()
{
	ActionComp->End_SecondaryAction();
}

void ACPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	RollingRotation();

	MontagesComp->PlayRoll();
}

void ACPlayer::Begin_Backstep()
{
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	MontagesComp->PlayBackstep();
}

void ACPlayer::RollingRotation()
{
	FVector Start, Target;
	FRotator Rotation;

	Start = GetActorLocation();

	if (GetVelocity().IsNearlyZero())
	{
		const FRotator& ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
		const FVector& ControlForward	= FQuat(ControlRotation).GetForwardVector();

		Target = Start + ControlForward;;
	}
	else
	{
		Target = Start + GetVelocity().GetSafeNormal2D();
	}

	Rotation = UKismetMathLibrary::FindLookAtRotation(Start, Target);
	SetActorRotation(Rotation);
}

void ACPlayer::Hitted()
{
	MontagesComp->PlayHitted();
	AttributeComp->SetStop();
}

void ACPlayer::Dead()
{
	//Ragdoll
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();
	GetMesh()->GetAnimInstance()->StopAllMontages(0.f);

	//Add Impulse
	FVector Start = GetActorLocation();
	FVector Target = DamageInstigator->GetPawn()->GetActorLocation();
	FVector Direction = Start - Target;
	Direction.Normalize();

	GetMesh()->AddImpulseAtLocation(Direction * DamageValue * 3000.f, Start);

	//Off All Collisions
	ActionComp->OffAllCollisions();

	// Disable Input
	DisableInput(GetController<APlayerController>());

	// PostProcess
	PostProcessComp->bEnabled = true;


	// End_Dead Timer
	UKismetSystemLibrary::K2_SetTimer(this, "End_Dead", 5.f, false);
}

void ACPlayer::End_Dead()
{
	ensure(GameOverWidgetClass);

	APlayerController* PC = GetController<APlayerController>();
	CheckNull(PC);

	UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(PC, GameOverWidgetClass);
	GameOverWidget->AddToViewport();

	PC->bShowMouseCursor = true;
	PC->SetInputMode(FInputModeGameAndUI());
}

void ACPlayer::End_Roll()
{
	UCActionData* CurrentDA = ActionComp->GetCurrentDataAsset();

	if (CurrentDA && CurrentDA->EquipmentData.bUseControlRotation)
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	//if (!StateComp->IsDeadMode())
	StateComp->SetIdleMode();
}

void ACPlayer::End_Backstep()
{
	// if (ÇöÀç ³»°¡ ÀåÂøÇÑ DA->bUseControl == 1, 0)
	UCActionData* CurrentDA = ActionComp->GetCurrentDataAsset();

	if (CurrentDA && !CurrentDA->EquipmentData.bUseControlRotation)
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}

	//if (!StateComp->IsDeadMode())

	StateComp->SetIdleMode();
}

void ACPlayer::RootKey(FLinearColor FindKey)
{
	Key.Add(FindKey, true);
}

void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Roll:
		{
			Begin_Roll();
		}
		break;
		
		case EStateType::Backstep:
		{
			Begin_Backstep();
		}
		break;

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
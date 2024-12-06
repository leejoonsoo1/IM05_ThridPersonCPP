#include "CAim.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Game/CHUD.h"

UCAim::UCAim()
{
	CHelpers::GetAsset(&AimCurve, "/Game/Curves/Curve_Aim");
}

void UCAim::Initialize(ACharacter* InOwnerCharacter)
{
	OwnerCharacter	= InOwnerCharacter;
	SpringArmComp	= CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	CameraComp		= CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	FOnTimelineFloat AimTimelineDelegate;
	AimTimelineDelegate.BindUFunction(this, "OnProgress");
	AimTimeline.AddInterpFloat(AimCurve, AimTimelineDelegate);

	if (SpringArmComp)
	{
		SpringArmComp->SocketOffset = FVector(0, 50, 40);
	}

	APlayerController* PC = OwnerCharacter->GetController<APlayerController>();

	if (PC)
	{
		HUD = PC->GetHUD<ACHUD>();
	}
}

void UCAim::Tick(float DeltaTime)
{
	AimTimeline.TickTimeline(DeltaTime);
}

void UCAim::On()
{
	CheckFalse(IsAvailable());
	CheckTrue(bZooming);

	bZooming = true;

	SpringArmComp->TargetArmLength	= 300.f;
	SpringArmComp->SocketOffset	= FVector(0, 50, 45);
	SpringArmComp->bEnableCameraLag	= false;

	// 1) PlayerController
	// 2) OwnerCharacter
	
	if (HUD)
	{
		HUD->EnableAimTextTure();	
	}

	AimTimeline.PlayFromStart();
}

void UCAim::Off()
{
	CheckFalse(IsAvailable());
	CheckFalse(bZooming);

	bZooming = false;

	SpringArmComp->TargetArmLength	= 500.f;
	SpringArmComp->SocketOffset	= FVector(0, 50, 40);
	SpringArmComp->bEnableCameraLag = true;

	if (HUD)
	{
		HUD->DisableAimTextTure();
	}

	AimTimeline.ReverseFromEnd();
}

void UCAim::OnProgress(float Output)
{
	CameraComp->FieldOfView = Output;
}

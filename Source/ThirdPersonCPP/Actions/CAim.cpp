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
	OwnerCharacter = InOwnerCharacter;
	SpringArmComp = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);
	CameraComp = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	FOnTimelineFloat AimTimelineDelegate;
	AimTimelineDelegate.BindUFunction(this, "OnProgress");
	AimTimeline.AddInterpFloat(AimCurve, AimTimelineDelegate);

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
	CheckFalse(IsAvaliable());
	CheckTrue(bZooming);

	bZooming = true;

	SpringArmComp->TargetArmLength = 250.f;
	SpringArmComp->SocketOffset = FVector(0, 60, 10);
	SpringArmComp->bEnableCameraLag = false;

	if(HUD)
	{
		HUD->EnableAimTexture();
	}
	
	AimTimeline.PlayFromStart();
}

void UCAim::Off()
{
	CheckFalse(IsAvaliable());
	CheckFalse(bZooming);

	bZooming = false;

	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->SocketOffset = FVector::ZeroVector;
	SpringArmComp->bEnableCameraLag = true;

	if (HUD)
	{
		HUD->DisableAimTexture();
	}

	AimTimeline.ReverseFromEnd();
}

void UCAim::OnProgress(float Output)
{
	CameraComp->FieldOfView = Output;
}

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "CAim.generated.h"

class ACharacter;
class USpringArmComponent;
class UCameraComponent;
class UCurveFloat;
class ACHUD;

UCLASS()
class THIRDPERSONCPP_API UCAim : public UObject
{
	GENERATED_BODY()
	
public:
	UCAim();

	void Initialize(ACharacter* InOwnerCharacter);
	void Tick(float DeltaTime);

	FORCEINLINE bool IsZooming() { return bZooming; }
	FORCEINLINE bool IsAvaliable() { return SpringArmComp && CameraComp; }

	void On();
	void Off();

private:
	UFUNCTION()
	void OnProgress(float Output);

private:
	ACharacter* OwnerCharacter;
	USpringArmComponent* SpringArmComp;
	UCameraComponent* CameraComp;

	bool bZooming;

	UCurveFloat* AimCurve;
	FTimeline AimTimeline;

	ACHUD* HUD;
};

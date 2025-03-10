#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "Components/CActionComponent.h"
#include "CDoAction_MagicBall.generated.h"

class UCAim;

UCLASS()
class THIRDPERSONCPP_API ACDoAction_MagicBall : public ACDoAction
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DelatTime) override;

public:
	virtual void PrimaryAction()		override;
	virtual void Begin_PrimaryAction()	override;
	virtual void End_PrimaryAction()	override;

	virtual void Begin_SecondaryAction()	override;
	virtual void End_SecondaryAction()		override;

	FORCEINLINE UCAim* GetAim() { return Aim; }

private:
	UFUNCTION()
	virtual void OnProjectileBeginOverlap(const FHitResult& InHitResult);

	UFUNCTION()
	void OnActionTypeChanged(EActionType InPrevType, EActionType InNewType);

private:
	UPROPERTY()
	UCAim* Aim;
};
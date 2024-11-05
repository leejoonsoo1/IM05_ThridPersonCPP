#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unaremd, Fist, OneHand, TwoHand, MagicBall, Warp, WhirlWind
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActionComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsUnarmedMode() const { return Type == EActionType::Unaremd; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsFistMode() const { return Type == EActionType::Fist; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsOneHandMode() const { return Type == EActionType::OneHand; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsTwoHandMode() const { return Type == EActionType::TwoHand; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsMagicBallMode() const { return Type == EActionType::MagicBall; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsWarpMode() const { return Type == EActionType::Warp; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsWhirlWindMode() const { return Type == EActionType::WhirlWind; }

	void SetUnarmedMode();
	void SetFistMode();
	void SetOneHandMode();
	void SetTwoHandMode();
	void SetMagicBallMode();
	void SetWarpMode();
	void SetWhirlWindMode();

private:
	void SetMode(EActionType InNewType);
	void ChangeType(EActionType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
	FActionTypeChanged OnActionTypeChanged;

private:
	EActionType Type;
};

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CAtionComponent.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unaremd, Fist, OneHand, TwoHand, MagicBall, Wrap, WhirlWind
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FActionTypeChanged, EActionType, InPrevType, EActionType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCAtionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCAtionComponent();

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
	FORCEINLINE bool IsWrapMode() const { return Type == EActionType::Wrap; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsWhirlWindMode() const { return Type == EActionType::WhirlWind; }

	void SetUnarmedMode();
	void SetFistMode();
	void SetOneHandMode();
	void SetTwoHandMode();
	void SetMagicBallMode();
	void SetWrapMode();
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

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActionComponent.generated.h"

class UCActionData;
class UCActionObject;

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Unarmed, Fist, OneHand, TwoHand, MagicBall, Warp, WhirlWind, Max
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
	void PrimaryAction();

	void Begin_SecondaryAction();
	void End_SecondaryAction();

	void OffAllCollisions();
	void DestroyAll();

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsUnarmedMode()		 const		{ return Type == EActionType::Unarmed; }
											 
	UFUNCTION(BlueprintCallable)			 
	FORCEINLINE bool IsFistMode()			 const		{ return Type == EActionType::Fist; }
											 
	UFUNCTION(BlueprintCallable)			 
	FORCEINLINE bool IsOneHandMode()		 const		{ return Type == EActionType::OneHand; }
											 
	UFUNCTION(BlueprintCallable)			 
	FORCEINLINE bool IsTwoHandMode()		 const		{ return Type == EActionType::TwoHand; }
											 
	UFUNCTION(BlueprintCallable)			 
	FORCEINLINE bool IsMagicBallMode()		 const		{ return Type == EActionType::MagicBall; }
											 
	UFUNCTION(BlueprintCallable)			 
	FORCEINLINE bool IsWarpMode()			 const		{ return Type == EActionType::Warp; }
											 
	UFUNCTION(BlueprintCallable)			 
	FORCEINLINE bool IsWhirlWindMode()		 const		{ return Type == EActionType::WhirlWind; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UCActionData* GetCurrentDataAsset()		{ return DataAssets[(int32)Type]; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UCActionObject* GetCurrentDataObject()	{ return DataObjects[(int32)Type]; }

	UFUNCTION(BlueprintCallable)
	void SetUnarmedMode();

	UFUNCTION(BlueprintCallable)
	void SetFistMode();

	UFUNCTION(BlueprintCallable)
	void SetOneHandMode();

	UFUNCTION(BlueprintCallable)
	void SetTwoHandMode();

	UFUNCTION(BlueprintCallable)
	void SetMagicBallMode();

	UFUNCTION(BlueprintCallable)
	void SetWarpMode();

	UFUNCTION(BlueprintCallable)
	void SetWhirlWindMode();

private:
	void SetMode(EActionType InNewType);
	void ChangeType(EActionType InNewType);

public:
	UPROPERTY(BlueprintAssignable)
	FActionTypeChanged OnActionTypeChanged;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
	UCActionData* DataAssets[(int32)EActionType::Max];

	UPROPERTY()
	UCActionObject* DataObjects[(int32)EActionType::Max];

private:
	EActionType Type;

};

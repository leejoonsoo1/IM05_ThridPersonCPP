#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

class UAnimMontage;
class ACharaacter;
class ACEquipment;
class ACAttachment;
class ACDoAction;
class UParticleSystem;
class UCameraShake;
class ACProjectile;

//-----------------------------------------------------------------------------
// Struct FEquipmentData
//-----------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UAnimMontage* Montage;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1.f;

	UPROPERTY(EditAnywhere)
	FName StartSection;

	UPROPERTY(EditAnywhere)
	bool bCanMove = true;

	// (true 카메라 앞 || false 키보드 누른) 방향을 바라본다.
	UPROPERTY(EditAnywhere)
	bool bUseControlRotation = true;

};

//-----------------------------------------------------------------------------
// Struct FActionData
//-----------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FActionData : public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Damage = 5.f;

	UPROPERTY(EditAnywhere)
	float HitStop;

	UPROPERTY(EditAnywhere)
	UParticleSystem* Effect;

	UPROPERTY(EditAnywhere)
	FTransform EffectTransform;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShake> ShakeClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACProjectile> ProjectileClass;
};

//-----------------------------------------------------------------------------
// Class UCActionData
//-----------------------------------------------------------------------------
UCLASS()
class THIRDPERSONCPP_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	void BeginPlay(ACharacter* InOwnerChacater);

	FORCEINLINE ACEquipment*	GetEquipment()	{ return Equipment; }
	FORCEINLINE ACAttachment*	GetAttachment()	{ return Attachment; }
	FORCEINLINE ACDoAction*		GetDoAction()	{ return DoAction; }

private:
	FString MakeLabel(ACharacter* InOwnerCharacter, FString InMiddleName);

public:
	UPROPERTY(EditAnywhere, Category = "Equipment")
	TSubclassOf<ACEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	FLinearColor EquipmentColor;

	// Equipment
	UPROPERTY(EditAnywhere, Category = "Equipment")
	FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere, Category = "Attachment")
	TSubclassOf<ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere, Category = "DoAction")
	TSubclassOf<ACDoAction> DoActionClass;

	UPROPERTY(EditAnywhere, Category = "DoAction")
	TArray<FActionData> DoActionDatas;

private:
	ACEquipment*	Equipment;
	ACAttachment*	Attachment;
	ACDoAction*		DoAction;
};

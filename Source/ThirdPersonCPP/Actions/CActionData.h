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

	// (true ī�޶� �� || false Ű���� ����) ������ �ٶ󺻴�.
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

	UPROPERTY(EditAnywhere, Category = "Attachment")
	TSubclassOf<ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere, Category = "Attachment")
	TSubclassOf<ACDoAction> DoActionClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	TArray<FActionData> DoActionDatas;

	// Equipment
	UPROPERTY(EditAnywhere, Category = "Equipment")
	FEquipmentData EquipmentData;

private:
	ACEquipment*	Equipment;
	ACAttachment*	Attachment;
	ACDoAction*		DoAction;
};

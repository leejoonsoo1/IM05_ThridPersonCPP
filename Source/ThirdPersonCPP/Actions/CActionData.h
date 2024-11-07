#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

class UAnimMontage;
class ACEquipment;
class ACharaacter;

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
UCLASS()
class THIRDPERSONCPP_API UCActionData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	void BeginPlay(ACharacter* InOwnerChacater);

	FORCEINLINE ACEquipment* GetEquipment() { return Equipment; }

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

private:
	ACEquipment* Equipment;
};

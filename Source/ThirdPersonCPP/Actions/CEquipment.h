#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActionData.h"
#include "CEquipment.generated.h"

class ACharacter;
class UCStateComponent;
class UCAttributeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentDelegate);

UCLASS()
class THIRDPERSONCPP_API ACEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEquipment();

protected:
	virtual void BeginPlay() override;

public:
	void SetData(FEquipmentData& InData);
	void SetColor(FLinearColor& InColor);

	FORCEINLINE const bool* IsEquipped() { return &bEquipped; }

public:
	UFUNCTION(BlueprintNativeEvent)
	void Equip();

	UFUNCTION(BlueprintNativeEvent)
	void UnEquip();

	UFUNCTION(BlueprintNativeEvent)
	void Begin_Equip();

	UFUNCTION(BlueprintNativeEvent)
	void End_Equip();


public:
	UPROPERTY(BlueprintAssignable)
	FEquipmentDelegate OnEquipmentDelegate;

	UPROPERTY(BlueprintAssignable)
	FEquipmentDelegate OnUnEquipmentDelegate;

protected:
	UPROPERTY(BlueprintReadOnly)
	ACharacter*	OwnerCharacter;

	UPROPERTY(BlueprintReadOnly)
	UCStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly)
	UCAttributeComponent* AttributeComp;

private:
	FEquipmentData	Data;
	FLinearColor	Color;

	bool bEquipped;
};

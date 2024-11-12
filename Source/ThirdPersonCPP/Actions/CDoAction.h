#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CActionData.h"
#include "CDoAction.generated.h"


class ACharacter;
class UCStateComponent;
class UCAttributeComponent;

UCLASS()
class THIRDPERSONCPP_API ACDoAction : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoAction();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetDatas(TArray<FActionData>& InDatas);

	virtual void PrimaryAction() {};
	virtual void Begin_PrimaryAction() {};
	virtual void End_PrimaryAction() {};

protected:
	UPROPERTY(BlueprintReadOnly, Interp, Category = "DoAction")
	ACharacter* OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, Interp, Category = "DoAction")
	UCStateComponent* StateComp;

	UPROPERTY(BlueprintReadOnly, Interp, Category = "DoAction")
	UCAttributeComponent* AttributeComp;

protected:
	TArray<FActionData> Datas;
};
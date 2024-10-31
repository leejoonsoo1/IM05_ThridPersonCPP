#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	// 호출 순서는 UpdateAnimation이 더 우선적으로 호출됨.
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player")
	float Speed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Player")
	float Direction;
};

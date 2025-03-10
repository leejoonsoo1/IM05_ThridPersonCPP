#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Components/CAttributeComponent.h"
#include "CBTTaskNode_Speed.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCBTTaskNode_Speed : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCBTTaskNode_Speed();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditInstanceOnly)
	EWalkSpeedType Type;
};

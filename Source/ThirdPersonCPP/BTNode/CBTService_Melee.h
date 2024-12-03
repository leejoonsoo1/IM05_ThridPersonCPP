#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_Melee.generated.h"

class ACAIController;
class UCBehaviorComponent;
class APawn;
class UCStateComponent;

UCLASS()
class THIRDPERSONCPP_API UCBTService_Melee : public UBTService
{
	GENERATED_BODY()

public:
	UCBTService_Melee();

protected:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
private:
	ACAIController*			AIC;
	UCBehaviorComponent*	BehaviorComp;
	APawn*					EnemyPawn;
	UCStateComponent*		StateComp;
};

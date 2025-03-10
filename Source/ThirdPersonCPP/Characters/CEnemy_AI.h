#pragma once

#include "CoreMinimal.h"
#include "Characters/CEnemy.h"
#include "CEnemy_AI.generated.h"

class UBehaviorTree;
class UCPatrolComponent;
UCLASS()
class THIRDPERSONCPP_API ACEnemy_AI : public ACEnemy
{
	GENERATED_BODY()

public:
	ACEnemy_AI();

	FORCEINLINE UBehaviorTree* GetBehaviorTree() { return BehaviorTree;	}

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCPatrolComponent* PatrolComp;

private:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

};

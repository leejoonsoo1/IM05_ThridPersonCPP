#include "CBTTaskNode_Speed.h"
#include "Global.h"
#include "AIController.h"

UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
    NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIC = OwnerComp.GetAIOwner();
    CheckNullResult(AIC, EBTNodeResult::Failed);

    APawn* EnemyPawn =  AIC->GetPawn();
    CheckNullResult(EnemyPawn, EBTNodeResult::Failed);

    UCAttributeComponent* AttributeComp =  CHelpers::GetComponent<UCAttributeComponent>(EnemyPawn);
    CheckNullResult(AttributeComp, EBTNodeResult::Failed);

    AttributeComp->SetSpeed(Type);

    return EBTNodeResult::Succeeded;
}

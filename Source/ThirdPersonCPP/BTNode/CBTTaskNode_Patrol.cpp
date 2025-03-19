#include "CBTTaskNode_Patrol.h"
#include "Global.h"
#include "AIController.h"
#include "Components/CPatrolComponent.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	NodeName = "Patrol";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIC = OwnerComp.GetAIOwner();
	CheckNullResult(AIC, EBTNodeResult::Failed);

	APawn* EnemyPawn = AIC->GetPawn();
	CheckNullResult(EnemyPawn, EBTNodeResult::Failed);

	UCPatrolComponent* PatrolComp = CHelpers::GetComponent<UCPatrolComponent>(EnemyPawn);
	CheckNullResult(PatrolComp, EBTNodeResult::Failed);

	CheckFalseResult(PatrolComp->IsPathValid(), EBTNodeResult::Failed);

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = OwnerComp.GetAIOwner();
	CheckNull(AIC);

	APawn* EnemyPawn = AIC->GetPawn();
	CheckNull(EnemyPawn);

	UCPatrolComponent* PatrolComp = CHelpers::GetComponent<UCPatrolComponent>(EnemyPawn);
	CheckNull(PatrolComp);

	FVector MoveToLocation;
	PatrolComp->GetMoveTo(MoveToLocation);

	EPathFollowingRequestResult::Type Result = AIC->MoveToLocation(MoveToLocation, 50, false);

	if (Result == EPathFollowingRequestResult::Failed)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (Result == EPathFollowingRequestResult::AlreadyAtGoal)
	{
		PatrolComp->UpdateNextIndex();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
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
	CLog::Log("UCBTTaskNode_Patrol::ExecuteTask");

	PatrolComp->GetMoveTo(MoveToLocation);

	EPathFollowingRequestResult::Type Result = AIC->MoveToLocation(MoveToLocation);

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
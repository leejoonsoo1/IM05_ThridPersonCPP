#include "CBTTaskNode_Action.h"
#include "Global.h"
#include "AIController.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"

UCBTTaskNode_Action::UCBTTaskNode_Action()
{
	NodeName = "Action";
	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_Action::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIC = OwnerComp.GetAIOwner();
	CheckNullResult(AIC, EBTNodeResult::Failed);

	APawn* EnemyPawn = AIC->GetPawn();
	CheckNullResult(EnemyPawn, EBTNodeResult::Failed);

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(EnemyPawn);
	CheckNullResult(ActionComp, EBTNodeResult::Failed);

	ActionComp->PrimaryAction();

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Action::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIC = OwnerComp.GetAIOwner();
	CheckNull(AIC);

	APawn* EnemyPawn = AIC->GetPawn();
	CheckNull(EnemyPawn);

	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(EnemyPawn);
	CheckNull(StateComp);

	if (StateComp->IsIdleMode())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

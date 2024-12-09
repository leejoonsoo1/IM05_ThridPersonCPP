#include "CBTTaskNode_ChangeAction.h"
#include "Global.h"
#include "AIController.h"
#include "Components/CActionComponent.h"
#include "Components/CStateComponent.h"
#include "Actions/CActionData.h"

UCBTTaskNode_ChangeAction::UCBTTaskNode_ChangeAction()
{
	NodeName = "ChangeAction";

	bNotifyTick = true;
}

EBTNodeResult::Type UCBTTaskNode_ChangeAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIC = OwnerComp.GetAIOwner();
	CheckNullResult(AIC, EBTNodeResult::Failed);

	APawn* EnemyPawn = AIC->GetPawn();
	CheckNullResult(EnemyPawn, EBTNodeResult::Failed);

	UCActionComponent* ActionComp = CHelpers::GetComponent<UCActionComponent>(EnemyPawn);
	CheckNullResult(ActionComp, EBTNodeResult::Failed);

	if (Type == EActionType::Warp && !ActionComp->IsWarpMode())
	{
		ActionComp->SetWarpMode();
	}
	else if (Type == EActionType::MagicBall && !ActionComp->IsMagicBallMode())
	{
		ActionComp->SetMagicBallMode();
	}

	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_ChangeAction::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	PrintLine();

	AAIController* AIC = OwnerComp.GetAIOwner();
	CheckNull(AIC);
	

	APawn* EnemyPawn = AIC->GetPawn();
	CheckNull(EnemyPawn);
	

	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(EnemyPawn);
	CheckNull(StateComp);


	if (StateComp->IsIdleMode())
	{
	}
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
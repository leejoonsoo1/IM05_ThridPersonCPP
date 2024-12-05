#include "CBTService_Melee.h"
#include "Global.h"
#include "Controller/CAIController.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CPatrolComponent.h"
#include "Characters/CPlayer.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "RootService";
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACAIController* AIC = Cast<ACAIController>(OwnerComp.GetAIOwner());
	CheckNull(AIC);

	UCBehaviorComponent* BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(AIC);
	CheckNull(BehaviorComp);

	APawn* EnemyPawn = AIC->GetPawn();
	CheckNull(EnemyPawn);

	UCStateComponent* StateComp = CHelpers::GetComponent<UCStateComponent>(EnemyPawn);
	CheckNull(StateComp);

	UCPatrolComponent* PatrolComp = CHelpers::GetComponent<UCPatrolComponent>(EnemyPawn);

	// Hitted
	if (StateComp->IsHittedMode())
	{
		BehaviorComp->SetHittedMode();

		return;
	}

	// Read Player From BB
	ACPlayer* Player = BehaviorComp->GetTargetPlayerValue();

	// No Perceived Player
	if (!Player)
	{
		if (PatrolComp && PatrolComp->IsPathValid())
		{
			BehaviorComp->SetPatrolMode();

			return;
		}

		BehaviorComp->SetWaitMode();
		
		return;
	}

	// Get Distance To
	float Distance = EnemyPawn->GetDistanceTo(Player);

	// Perceived Player
	
	//In Action Range
	if (Distance < AIC->GetBehaviorRange())
	{
		BehaviorComp->SetActionMode();

		return;
	}

	// In Sight Range
	if (Distance < AIC->GetSightRadius())
	{
		BehaviorComp->SetApproachMode();

		return;
	}
}
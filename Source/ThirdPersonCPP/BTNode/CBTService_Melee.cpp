#include "CBTService_Melee.h"
#include "Global.h"
#include "Controller/CAIController.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CPatrolComponent.h"
#include "Characters/CPlayer.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "RootService_Melee";
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
	//CheckNull(PatrolComp);

	//Dead
	if (StateComp->IsDeadMode())
	{
		BehaviorComp->SetWaitMode();
		AIC->GetBrainComponent()->StopLogic("Dead");
		return;
	}

	//Hitted
	if (StateComp->IsHittedMode())
	{
		BehaviorComp->SetHittedMode();
		return;
	}

	//Read Player from BB
	ACPlayer* Player = BehaviorComp->GetPlayerValue();
	
	//No Perceived Player
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

	//Get Distance To
	float Distance = EnemyPawn->GetDistanceTo(Player);
	
	//Perceived Player
	UCStateComponent* OtherStateComp = CHelpers::GetComponent<UCStateComponent>(Player);
	if (OtherStateComp && OtherStateComp->IsDeadMode())
	{
		BehaviorComp->SetWaitMode();
		return;
	}

	//In Action Range
	if (Distance < AIC->GetBehaviorRange())
	{
		BehaviorComp->SetActionMode();
		return;
	}

	//In Sight Range
	if (Distance < AIC->GetSightRadius())
	{
		BehaviorComp->SetApproachMode();
		return;
	}
}
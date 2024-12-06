#include "CBTService_Wizard.h"
#include "Global.h"
#include "Controller/CAIController.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Characters/CPlayer.h"

UCBTService_Wizard::UCBTService_Wizard()
{
	NodeName = "RootService_Wizard";
}

void UCBTService_Wizard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	// Dead
	if (StateComp->IsDeadMode())
	{
		BehaviorComp->SetWaitMode();
		AIC->GetBrainComponent()->StopLogic("Dead");

		return;
	}

	// Hitted
	if (StateComp->IsHittedMode())
	{
		BehaviorComp->SetHittedMode();

		return;
	}

	//Read Player from BB
	ACPlayer* Player = BehaviorComp->GetTargetPlayerValue();

	//No Perceived Player
	if (!Player)
	{
		BehaviorComp->SetWaitMode();
		AIC->ClearFocus(EAIFocusPriority::LastFocusPriority);

		return;
	}

	//Get Distance To
	float Distance = EnemyPawn->GetDistanceTo(Player);

	//Perceived Player
	AIC->SetFocus(Player);

	//In Action Range
	if (Distance < AIC->GetBehaviorRange())
	{
		BehaviorComp->SetRunAwayMode();

		return;
	}

	//In Sight Range
	if (Distance < AIC->GetSightRadius())
	{
		BehaviorComp->SetActionMode();
		return;
	}
}
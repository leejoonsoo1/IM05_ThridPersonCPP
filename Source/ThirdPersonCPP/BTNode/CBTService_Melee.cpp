#include "CBTService_Melee.h"
#include "Global.h"
#include "Controller/CAIController.h"
#include "Components/CBehaviorComponent.h"
#include "Components/CStateComponent.h"
#include "Characters/CPlayer.h"

UCBTService_Melee::UCBTService_Melee()
{
	NodeName = "RootService";
}

void UCBTService_Melee::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);

	AIC = Cast<ACAIController>(SearchData.OwnerComp.GetAIOwner());
	CheckNull(AIC);

	BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(AIC);
	CheckNull(BehaviorComp);

	EnemyPawn = AIC->GetPawn();
	CheckNull(EnemyPawn);

	StateComp = CHelpers::GetComponent<UCStateComponent>(EnemyPawn);
}

void UCBTService_Melee::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckNull(AIC);
	CheckNull(BehaviorComp);
	CheckNull(EnemyPawn);
	CheckNull(StateComp);

	// Hitted
	if (StateComp->IsHittedMode())
	{
		BehaviorComp->SetHittedMode();

		CLog::Log(__FUNCTION__, __LINE__);
		CLog::Log("UCBTService_Melee::TickNode");

		return;
	}

	// Read Player From BB
	ACPlayer* Player = BehaviorComp->GetTargetPlayerValue();

	// No Perceived Player
	if (!Player)
	{
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
// Fill out your copyright notice in the Description page of Project Settings.


#include "CAIController.h"
#include "Global.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Characters/CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create BlackboardComponent
	CHelpers::CreateActorComponent<UAIPerceptionComponent>	(this,	&PerceptionComp,	"PerceptionComp");
	CHelpers::CreateActorComponent<UBlackboardComponent>	(this,	&Blackboard,		"Blackboard");
	CHelpers::CreateActorComponent<UCBehaviorComponent>		(this,	&BehaviorComp,		"BehaviorComp");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>	("Sight");

	Sight->SightRadius								= 600.f;
	Sight->LoseSightRadius							= 800.f;
	Sight->PeripheralVisionAngleDegrees				= 90.f;
	Sight->SetMaxAge(2.f);

	Sight->DetectionByAffiliation.bDetectEnemies	= true;
	Sight->DetectionByAffiliation.bDetectNeutrals	= false;
	Sight->DetectionByAffiliation.bDetectFriendlies	= false;

	PerceptionComp->ConfigureSense(*Sight);	

	TeamID = 1;

	//PerceptionComp->OnPerceptionUpdated
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedEnemy = Cast<ACEnemy_AI>(InPawn);

	if (PossessedEnemy && ensure(PossessedEnemy->GetBehaviorTree()))
	{
		UseBlackboard(PossessedEnemy->GetBehaviorTree()->GetBlackboardAsset(), Blackboard);
		RunBehaviorTree(PossessedEnemy->GetBehaviorTree());
	}

	SetGenericTeamId(TeamID);
	BehaviorComp->SetBlackboardComponent(Blackboard);
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#include "CEnvQueryContext_Player.h"
#include "Global.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "GameFramework/Character.h"
#include "Components/CBehaviorComponent.h"
#include "Characters/CPlayer.h"

void UCEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	//1. UGameplayStatics::GetPlayerCharacter();
	ACharacter* Querior = Cast<ACharacter>(QueryInstance.Owner.Get());
	if (Querior)
	{
		UCBehaviorComponent* BehaviorComp = CHelpers::GetComponent<UCBehaviorComponent>(Querior->GetController());
		if (BehaviorComp)
		{
			ACPlayer* Player = BehaviorComp->GetTargetPlayerValue();
			if (Player)
			{
				UEnvQueryItemType_Actor::SetContextHelper(ContextData, Player);
				return;
			}
		}
	}

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, UGameplayStatics::GetPlayerPawn(Querior->GetWorld(), 0));

	//2. QueryInstance.Owner -> Querior -> AIC -> BB -> PlayerKey

}
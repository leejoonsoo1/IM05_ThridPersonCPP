#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

class ACEnemy_AI;
class UCBehaviorComponent;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;

UCLASS()
class THIRDPERSONCPP_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACAIController();

	float GetSightRadius();
	
	FORCEINLINE float GetBehaviorRange() { return BehaviorRange; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCBehaviorComponent* BehaviorComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UAIPerceptionComponent* PerceptionComp;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	uint8 TeamID;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	bool bDrawRange;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float AdjustHeight;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	float BehaviorRange;

private:
	ACEnemy_AI* PossessedEnemy;

	UAISenseConfig_Sight* Sight;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPatrolPath.generated.h"

class USplineComponent;
class UTextRenderComponent;

UCLASS()
class THIRDPERSONCPP_API ACPatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPatrolPath();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

public:
	FORCEINLINE USplineComponent* GetSplineComponent() { return SplineComp; }

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USplineComponent* SplineComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UTextRenderComponent* TextComp;

private:
	UPROPERTY(EditInstanceOnly, Category = "Spline")
	bool bClosedLoop;

};

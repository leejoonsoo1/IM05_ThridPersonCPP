#include "CPatrolComponent.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "BTNode/CPatrolPath.h"

bool UCPatrolComponent::GetMoveTo(FVector& OutLocation)
{
	OutLocation = FVector(-1, -1, -1);
	CheckFalseResult(IsPathValid(), false);

	OutLocation = PatrolPath->GetSplineComponent()->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::World);
	return true;
}

void UCPatrolComponent::UpdateNextIndex()
{
	CheckFalse(IsPathValid());

	int32 Count = PatrolPath->GetSplineComponent()->GetNumberOfSplinePoints();

	//Reverse
	if (bReverse)
	{
		if (Index > 0)
		{
			Index--;
			return;
		}

		if (PatrolPath->GetSplineComponent()->IsClosedLoop())
		{
			Index = Count - 1;
			return;
		}

		Index = 1;
		bReverse = false;

		return;
	}

	//Forward
	if (Index < Count - 1)
	{
		Index++;
		return;
	}

	if (PatrolPath->GetSplineComponent()->IsClosedLoop())
	{
		Index = 0;
		return;
	}

	Index = Count - 2;
	bReverse = true;
}

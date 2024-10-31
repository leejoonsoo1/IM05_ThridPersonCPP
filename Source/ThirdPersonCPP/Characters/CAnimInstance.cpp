#include "CAnimInstance.h"
#include "Global.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* OwnerPawn = TryGetPawnOwner();
	CheckNull(OwnerPawn);

	Speed = OwnerPawn->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerPawn->GetVelocity(), OwnerPawn->GetControlRotation());
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

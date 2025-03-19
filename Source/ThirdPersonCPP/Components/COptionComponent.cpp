#include "COptionComponent.h"

UCOptionComponent::UCOptionComponent()
{
	MouseXSpeed = 90.f;
	MouseYSpeed = 45.f;

	ZoomSpeed = 1000.f;
	ZoomRange = FVector2D(100.f, 500.f);
}

void UCOptionComponent::SetMouseXSpeed(float InSpeed)
{
	MouseXSpeed = InSpeed;
}

void UCOptionComponent::SetMouseYSpeed(float InSpeed)
{
	MouseYSpeed = InSpeed;
}

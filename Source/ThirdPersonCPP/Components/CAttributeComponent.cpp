#include "CAttributeComponent.h"

UCAttributeComponent::UCAttributeComponent()
{
	SneakSpeed	= 200.f;
	WalkSpeed	= 400.f;
	SprintSpeed = 600.f;

	bCanMove = true;

}

void UCAttributeComponent::SetMove()
{
	bCanMove = true;
}

void UCAttributeComponent::SetStop()
{
	bCanMove = false;
}

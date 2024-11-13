#include "CHealthWidget.h"
#include "Components/ProgressBar.h"

void UCHealthWidget::Update(float InCurrentHealth, float InMaxHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(InCurrentHealth / InMaxHealth);
	}
}
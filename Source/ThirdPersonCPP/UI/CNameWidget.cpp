#include "CNameWidget.h"
#include "Components/TextBlock.h"

void UCNameWidget::SetNameText(const FString& InControllerName, const FString& InPawnName)
{
	if (ControllerName)
	{
		ControllerName->SetText(FText::FromString(InControllerName));
	}

	if (PawnName)
	{
		PawnName->SetText(FText::FromString(InPawnName));
	}

}
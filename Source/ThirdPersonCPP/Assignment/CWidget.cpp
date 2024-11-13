#include "CWidget.h"
#include "Components/Image.h"
#include "Global.h"

void UCWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Map.Add(FLinearColor::Red,		Red);
	Map.Add(FLinearColor::Green,	Green);
	Map.Add(FLinearColor::Blue,		Blue);

	Red		->SetBrushTintColor(FSlateColor(FLinearColor(0.f, 0.f, 0.f)));
	Green	->SetBrushTintColor(FSlateColor(FLinearColor(0.f, 0.f, 0.f)));
	Blue	->SetBrushTintColor(FSlateColor(FLinearColor(0.f, 0.f, 0.f)));
}

void UCWidget::SetKey(FLinearColor InColor)
{
	UImage** RetrievedImage = Map.Find(InColor);

	if (RetrievedImage)
	{
		UImage* FoundImage = *RetrievedImage;
		FoundImage->SetBrushTintColor(FSlateColor(InColor));
		FoundImage->ColorAndOpacity.A = 1.0f;
	}
}
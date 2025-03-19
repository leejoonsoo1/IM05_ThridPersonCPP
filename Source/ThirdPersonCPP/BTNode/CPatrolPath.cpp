#include "CPatrolPath.h"
#include "Global.h"
#include "Components/SplineComponent.h"
#include "Components/TextRenderComponent.h"

ACPatrolPath::ACPatrolPath()
{
	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CHelpers::CreateSceneComponent(this, &SplineComp, "SplineComp", RootComp);
	CHelpers::CreateSceneComponent(this, &TextComp, "TextComp", RootComp);

	SplineComp->SetRelativeLocation(FVector(0, 0, 30));
	
	SplineComp->bShouldVisualizeScale = true;
	SplineComp->ScaleVisualizationWidth = 30.f;
	SplineComp->EditorUnselectedSplineSegmentColor = FLinearColor::Red;

	TextComp->SetRelativeLocation(FVector(0, 0, 100));
	TextComp->SetRelativeRotation(FRotator(0, 180, 0));
	TextComp->SetHorizontalAlignment(EHTA_Center);
	TextComp->SetTextRenderColor(FColor::Red);
	TextComp->SetWorldSize(80);

	bRunConstructionScriptOnDrag = false;
}

void ACPatrolPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	TextComp->SetText(GetName());
	
	SplineComp->SetClosedLoop(bClosedLoop);
}

void ACPatrolPath::BeginPlay()
{
	Super::BeginPlay();
	
	TextComp->SetVisibility(false);
}

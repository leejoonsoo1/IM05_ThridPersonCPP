#include "CChest.h"
#include "Global.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/BoxComponent.h"

ACChest::ACChest()
{
	CHelpers::CreateSceneComponent(this, &RootComp,			"RootComp");
	CHelpers::CreateSceneComponent(this, &BottomMeshComp,	"BottomMeshComp",	RootComp);
	CHelpers::CreateSceneComponent(this, &TopMeshComp,		"TopMeshComp",		BottomMeshComp);
	CHelpers::CreateSceneComponent(this, &BoxCollision,		"BoxCollision",		BottomMeshComp);

	UStaticMesh* TopMeshAsset, * BottomMeshAsset;
	CHelpers::GetAsset(&TopMeshAsset,		"/Game/Assignment/Chest/SM_ChestTop");
	CHelpers::GetAsset(&BottomMeshAsset,	"/Game/Assignment/Chest/SM_ChestBottom");

	TopMeshComp->SetStaticMesh(TopMeshAsset);
	BottomMeshComp->SetStaticMesh(BottomMeshAsset);

	SymbolColor = FLinearColor(0.f, 50.f, 0.f);
	bRunConstructionScriptOnDrag = false;
	BoxCollision->SetBoxExtent(FVector(64.f, 64.f, 64.f));

	Toggle = false;

}

void ACChest::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UMaterialInterface* Material;
	CHelpers::GetAssetDynamic(&Material, "/Game/Assignment/Chest/MI_Chest");

	if (Material)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);

		if (DynamicMaterial)
		{
			TopMeshComp->SetMaterial(0, DynamicMaterial);
			BottomMeshComp->SetMaterial(0, DynamicMaterial);

			DynamicMaterial->SetVectorParameterValue("SymbolColor", SymbolColor);
		}
	}
}

// Called when the game starts or when spawned
void ACChest::BeginPlay()
{
	Super::BeginPlay();
}

void ACChest::Interact() 
{
	if (Toggle)
	{
		TopMeshComp->SetRelativeRotation(FQuat(FRotator(0, 0, 0)));
		Toggle = false;
	}
	else
	{
		TopMeshComp->SetRelativeRotation(FQuat(FRotator(160, 0, 0)));
		Toggle = true;
	}
}
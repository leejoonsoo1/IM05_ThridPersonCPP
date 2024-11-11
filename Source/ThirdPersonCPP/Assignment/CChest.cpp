#include "CChest.h"
#include "Global.h"
#include "Materials/MaterialInstanceDynamic.h"

ACChest::ACChest()
{
	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");
	CHelpers::CreateSceneComponent(this, &BottomMeshComp, "BottomMeshComp", RootComp);
	CHelpers::CreateSceneComponent(this, &TopMeshComp, "TopMeshComp", BottomMeshComp);

	UStaticMesh* TopMeshAsset, * BottomMeshAsset;
	CHelpers::GetAsset(&TopMeshAsset, "/Game/Assignment/Chest/SM_ChestTop");
	CHelpers::GetAsset(&BottomMeshAsset, "/Game/Assignment/Chest/SM_ChestBottom");

	TopMeshComp->SetStaticMesh(TopMeshAsset);
	BottomMeshComp->SetStaticMesh(BottomMeshAsset);

	SymbolColor = FLinearColor(0, 50, 0);
	bRunConstructionScriptOnDrag = false;
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
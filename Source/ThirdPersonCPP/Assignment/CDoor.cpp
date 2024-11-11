#include "CDoor.h"
#include "Global.h"
#include "Materials/MaterialInstanceDynamic.h"

ACDoor::ACDoor()
{
	CHelpers::CreateSceneComponent(this, &RootComp,			"RootComp");
	CHelpers::CreateSceneComponent(this, &FrameMeshComp,	"FrameMeshComp",	RootComp);
	CHelpers::CreateSceneComponent(this, &DoorMeshComp,		"DoorMeshComp",		FrameMeshComp);

	UStaticMesh* FramMeshAsset, * DoorMeshAsset;

	CHelpers::GetAsset(&FramMeshAsset, "/Game/Assignment/Door/SM_DoorFrame");
	CHelpers::GetAsset(&DoorMeshAsset, "/Game/Assignment/Door/SM_Door");

	DoorMeshComp->SetRelativeLocation(FVector(0, 45, 0));

	FrameMeshComp->SetStaticMesh(FramMeshAsset);
	DoorMeshComp->SetStaticMesh(DoorMeshAsset);

	SymbolColor = FLinearColor(0, 1000, 0);
	bRunConstructionScriptOnDrag = false;
}

void ACDoor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UMaterialInterface* Material;
	CHelpers::GetAssetDynamic(&Material, "/Game/Assignment/Chest/MI_Chest");

	if (Material)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);

		if (DynamicMaterial)
		{
			FrameMeshComp->SetMaterial(0, DynamicMaterial);
			DoorMeshComp->SetMaterial(0, DynamicMaterial);

			DynamicMaterial->SetVectorParameterValue("SymbolColor", SymbolColor);
		}
	}
}

// Called when the game starts or when spawned
void ACDoor::BeginPlay()
{
	Super::BeginPlay();
	
}
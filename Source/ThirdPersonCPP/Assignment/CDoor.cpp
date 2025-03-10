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

	//DoorMeshComp->SetRelativeLocation(FVector(0, 1, 0));

	FrameMeshComp->SetStaticMesh(FramMeshAsset);
	DoorMeshComp->SetStaticMesh(DoorMeshAsset);

	SymbolColor = FLinearColor(0.f, 100.f, 0.f);
	bRunConstructionScriptOnDrag = false;

	Toggle = false;
}

void ACDoor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UMaterialInterface* Material;
	CHelpers::GetAssetDynamic(&Material, "/Game/Assignment/Door/MI_Door");

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

void ACDoor::BeginPlay()
{
	Super::BeginPlay();
}

void ACDoor::Interact()
{
	if (Toggle)
	{
		DoorMeshComp->SetRelativeRotation(FQuat(FRotator(0, 0, 0)));
		Toggle = false;
	}
	else
	{
		DoorMeshComp->SetRelativeRotation(FQuat(FRotator(0, 90, 0)));
		Toggle = true;
	}
}

FLinearColor ACDoor::GetSymbolColor()
{
	return SymbolColor;
}
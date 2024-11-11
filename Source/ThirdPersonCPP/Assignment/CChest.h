#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CChest.generated.h"

class UMaterialInstanceDynamic;

UCLASS()
class THIRDPERSONCPP_API ACChest : public AActor
{
	GENERATED_BODY()
	
public:	
	ACChest();

protected:
	virtual void OnConstruction(const FTransform& Transform)override;
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent*		RootComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent*	TopMeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent*	BottomMeshComp;

private:
	UPROPERTY(EditInstanceOnly, Category = "SysmbolColor")
	FLinearColor SymbolColor;

private:
	UMaterialInstanceDynamic* DynamicMaterial;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDoor.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoor();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

public:
	void Interact();
	FLinearColor GetSymbolColor();

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* FrameMeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* DoorMeshComp;

	UPROPERTY(EditInstanceOnly, Category = "SysmbolColor")
	FLinearColor SymbolColor;

private:
	class UMaterialInstanceDynamic* DynamicMaterial;

private:
	bool Toggle;
};

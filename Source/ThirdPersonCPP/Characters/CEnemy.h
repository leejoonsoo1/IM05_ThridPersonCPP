#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CCharacterInterface.h"
#include "CEnemy.generated.h"

class UCAttributeComponent;
class UCStateComponent;
class UCMontagesComponent;
class UCActionComponent;
class UWidgetComponent;

UCLASS()
class THIRDPERSONCPP_API ACEnemy : public ACharacter, public ICCharacterInterface
{
	GENERATED_BODY()

public:
	ACEnemy();

public:
	virtual void SetBodyColor(FLinearColor InColor) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent*	AttributeComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCStateComponent*		StateComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCMontagesComponent*	MontagesComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCActionComponent*		ActionComp;	
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent*		NameWidgetComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UWidgetComponent*		HealthWidgetComp;


protected:
	virtual void BeginPlay() override;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/CCharacterInterface.h"
#include "Components/CStateComponent.h"
#include "Components/TimelineComponent.h"
#include "CEnemy.generated.h"

class UCAttributeComponent;
class UCStateComponent;
class UCMontagesComponent;
class UCActionComponent;
class UWidgetComponent;
class UCurveFloat;

UCLASS()
class THIRDPERSONCPP_API ACEnemy : public ACharacter, public ICCharacterInterface
{
	GENERATED_BODY()

public:
	ACEnemy();

protected:
	void BeginPlay() override;

public:
	virtual void	Tick(float DeltaTime) override;
	virtual float	TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void	SetBodyColor(FLinearColor InColor) override;

private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	void Hitted()	override;
	void Dead()		override;

	UFUNCTION()
	void ResotreBodyColor();

	UFUNCTION()
	void OnProgressDissolve(float Output);

	UFUNCTION()
	void OnFinishDissolve();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly,	Category = "Components")
	UCAttributeComponent*	AttributeComp;

	UPROPERTY(VisibleDefaultsOnly,						Category = "Components")
	UCStateComponent*		StateComp;

	UPROPERTY(VisibleDefaultsOnly,						Category = "Components")
	UCMontagesComponent*	MontagesComp;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly,	Category = "Components")
	UCActionComponent*		ActionComp;	
	
	UPROPERTY(VisibleDefaultsOnly,						Category = "Components")
	UWidgetComponent*		NameWidgetComp;

	UPROPERTY(VisibleDefaultsOnly,						Category = "Components")
	UWidgetComponent*		HealthWidgetComp;

	UPROPERTY(EditAnywhere,								Category = "Hiited")
	float					LaunchValue;

	UPROPERTY(EditAnywhere,								Category = "Dissolve")
	UCurveFloat*			DissolveCurve;

	UPROPERTY(EditAnywhere,								Category = "Debug")
	bool					bVisibleNameWidget;

private:
	AController* DamageInstigator;
	float DamageValue;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* DissolveMaterial;

	FTimeline DissolveTimeline;
};
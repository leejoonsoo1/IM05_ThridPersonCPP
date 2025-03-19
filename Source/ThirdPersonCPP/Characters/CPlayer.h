#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "Components/CStateComponent.h"
#include "Interfaces/CCharacterInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCAttributeComponent;
class UCOptionComponent;
class UCStateComponent;
class UCMontagesComponent;
class UCActionComponent;
class UMaterialInstanceDynamic;
class UPostProcessComponent;
class UMaterialInstanceConstant;
class UCFeetComponent;

UCLASS()
class THIRDPERSONCPP_API ACPlayer : public ACharacter, public ICCharacterInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

	void SetBodyColor(FLinearColor InColor) override;
	virtual FGenericTeamId GetGenericTeamId() const override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);
	void OnTurn(float Axis);
	void OnLookUp(float Axis);
	void OnZoom(float Axis);

	void OnEvade();
	void OnWalk();
	void OffWalk();

	void OnFist();
	void OnOneHand();
	void OnTwoHand();
	void OnMagicBall();
	void OnWarp();
	void OnWhirlWind();

	void OnPrimaryAction();
	void OnBeginSecondaryAction();
	void OnEndSecondaryAction();


private:
	void Begin_Roll();
	void Begin_Backstep();

	void RollingRotation();

	void Hitted() override;
	void Dead() override;

	UFUNCTION()
	void End_Dead() override;

public:
	void End_Roll();
	void End_Backstep();

private:
	UFUNCTION()
	void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCAttributeComponent* AttributeComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCOptionComponent* OptionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCStateComponent* StateComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCMontagesComponent* MontagesComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCActionComponent* ActionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UCFeetComponent* FeetComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UPostProcessComponent* PostProcessComp;
	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Team")
	uint8 TeamID;

	UPROPERTY(EditDefaultsOnly, Category = "Dead")
	UMaterialInstanceConstant* PostProcessMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Dead")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	AController* DamageInstigator;
	float DamageValue;
};

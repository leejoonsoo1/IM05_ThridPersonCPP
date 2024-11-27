#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_WhirlWind.generated.h"

class UBoxComponent;

UCLASS()
class THIRDPERSONCPP_API ACDoAction_WhirlWind : public ACDoAction
{
	GENERATED_BODY()

public:
	ACDoAction_WhirlWind();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void PrimaryAction() 		override;
	virtual void Begin_PrimaryAction()	override;
	virtual void End_PrimaryAction()	override;
	virtual void Abort()				override;

public:
	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)	override;
																																																					
	virtual void OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)		override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "WhirlWind")
	float DamageToTime;

	UPROPERTY(EditDefaultsOnly, Category = "WhirlWind")
	float ActiveTime;

	UPROPERTY(EditDefaultsOnly, Category = "WhirlWind")
	float AroundSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "WhirlWind")
	float Radius;

private:
	UBoxComponent* BoxComp;
	bool bActivation;

	TArray<ACharacter*> HittedCharacters;
	float CurrentYaw;
};
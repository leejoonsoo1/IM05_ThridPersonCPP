#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDoAction.h"
#include "CDoAction_Melee.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACDoAction_Melee : public ACDoAction
{
	GENERATED_BODY()
	
public:
	virtual void PrimaryAction() override;
	virtual void Begin_PrimaryAction() override;
	virtual void End_PrimaryAction() override;

	virtual void OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter) override;

private:
	int32 ComboCount;
};

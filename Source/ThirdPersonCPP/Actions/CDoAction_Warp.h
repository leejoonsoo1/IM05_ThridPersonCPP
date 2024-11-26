#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Warp.generated.h"

class USkeletalMeshComponent;

UCLASS()
class THIRDPERSONCPP_API ACDoAction_Warp : public ACDoAction
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime)	override;

public:
	virtual void PrimaryAction()		override;
	virtual void Begin_PrimaryAction()	override;
	virtual void End_PrimaryAction()	override;

private:
	bool GetCursorLocation(FVector& OutLocation);

private:
	USkeletalMeshComponent* PreviewMeshComp;
	FVector LocationToWarp;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CCharacterInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class THIRDPERSONCPP_API ICCharacterInterface
{
	GENERATED_BODY()

public:
	virtual void SetBodyColor(FLinearColor InColor) = 0;
	
	virtual void Hitted() = 0;
	virtual void Dead() = 0;
	virtual void End_Dead() {}
};

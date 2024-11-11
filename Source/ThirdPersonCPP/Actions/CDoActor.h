#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDoActor.generated.h"

UCLASS()
class THIRDPERSONCPP_API ACDoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDoActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};

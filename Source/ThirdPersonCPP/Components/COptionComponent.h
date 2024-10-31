#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COptionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCOptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCOptionComponent();

	FORCEINLINE float GetMouseXSpeed() { return MouseXSpeed; }
	FORCEINLINE float GetMouseYSpeed() { return MouseYSpeed; }

	void SetMouseXSpeed(float InSpeed);
	void SetMouseYSpeed(float InSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mouse")
	float MouseXSpeed;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mouse")
	float MouseYSpeed;
};

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

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMouseXSpeed() const { return MouseXSpeed; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMouseYSpeed() const { return MouseYSpeed; }

	UFUNCTION(BlueprintCallable)
	void SetMouseXSpeed(float InSpeed);

	UFUNCTION(BlueprintCallable)
	void SetMouseYSpeed(float InSpeed);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetZoomSpeed() const { return ZoomSpeed; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetZoomMin() const { return ZoomRange.X; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetZoomMax() const { return ZoomRange.Y; }

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mouse")
	float MouseXSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mouse")
	float MouseYSpeed;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mouse")
	float ZoomSpeed;
		
	//x is min range, y is max range
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Mouse")
	FVector2D ZoomRange;
};

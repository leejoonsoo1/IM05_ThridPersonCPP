#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CHealthWidget.generated.h"

class UProgressBar;

UCLASS()
class THIRDPERSONCPP_API UCHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Update(float InCurrentHealth, float InMaxHealth);
	
private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
};

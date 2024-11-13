#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CNameWidget.generated.h"

class UTextBlock;

UCLASS()
class THIRDPERSONCPP_API UCNameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetNameText(const FString& InControllerName, const FString& InPawnName);
		
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ControllerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PawnName;
};

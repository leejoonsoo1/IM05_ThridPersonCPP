#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Containers/Map.h"
#include "CWidget.generated.h"

UCLASS()
class THIRDPERSONCPP_API UCWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void SetKey(FLinearColor InColor);

public:
	UPROPERTY(meta = (BindWidget))
	class UImage* Red;

	UPROPERTY(meta = (BindWidget))
	class UImage* Green;

	UPROPERTY(meta = (BindWidget))
	class UImage* Blue;

private:
	TMap<FLinearColor, UImage*> Map;
};
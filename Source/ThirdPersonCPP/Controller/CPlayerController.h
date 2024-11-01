#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UUserWidget;

UCLASS()
class THIRDPERSONCPP_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent();

public:
	UFUNCTION(BlueprintCallable, Exec)
	void ToggleOptionMenu();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> OptionMenuClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* OptionMenu;
};

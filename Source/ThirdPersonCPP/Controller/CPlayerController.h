#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UUserWidget;

UCLASS()
class THIRDPERSONCPP_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

protected:
	virtual void SetupInputComponent()		override;

public:
	UFUNCTION(BlueprintCallable, Exec)
	void ToggleOptionMenu();

private:
	void EnableSelectActionWidget();
	void DisableSelectActionWidget();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> OptionMenuClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* OptionMenu;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> SelectActinoWidgetClass;
	
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	UUserWidget* SelectActionWidget;
};

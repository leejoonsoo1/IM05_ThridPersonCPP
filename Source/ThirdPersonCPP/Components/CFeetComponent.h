#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CFeetComponent.generated.h"

class ACharacter;

USTRUCT(BlueprintType)
struct FFeetData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector LeftDistance;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector RightDistance;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FVector PelvisDistance;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FRotator LeftRotation;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FRotator RightRotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCFeetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCFeetComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE const FFeetData& GetData() { return Data; }

private:
	void Trace(FName InSoket, float& OutDistance, FRotator& OutRotation);

private:
	UPROPERTY(EditDefaultsOnly, Category = "IK")
	FName LeftSocket;

	UPROPERTY(EditDefaultsOnly, Category = "IK")
	FName RightSocket;

	UPROPERTY(EditDefaultsOnly, Category = "IK")
	float Additional;

	UPROPERTY(EditDefaultsOnly, Category = "IK")
	float FootHeight;

	UPROPERTY(EditDefaultsOnly, Category = "IK")
	float InterpSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "IK")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;
		
private:
	FFeetData Data;

	ACharacter* OwnerCharacter;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet\KismetSystemLibrary.h"
#include "CFeetComponent.generated.h"

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

UCLASS()
class THIRDPERSONCPP_API ACFeetComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	ACFeetComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FORCEINLINE const FFeetData& GetData() { return Data; }

private:
	void Trace(FName InSocket, float& OutDistance);

private:
	UPROPERTY(EditInstanceOnly, Category = "IK")
	FName LeftSocket;

	UPROPERTY(EditInstanceOnly, Category = "IK")
	FName RightSocket;

	UPROPERTY(EditInstanceOnly, Category = "IK")
	float Additinal;

	UPROPERTY(EditInstanceOnly, Category = "IK")
	float FootHeight;

	UPROPERTY(EditInstanceOnly, Category = "IK")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

private:
	FFeetData Data;

	ACharacter* OwnerCharacter;
};

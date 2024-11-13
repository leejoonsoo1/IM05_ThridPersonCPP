#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAttachment.generated.h"

class ACharacter;
class UShapeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAttachmentBeginOverlap, ACharacter*, InAttacker, AActor*, InCauser, ACharacter*, InOtherCharacter);

//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SixParams(FComponentBeginOverlapSignature, UPrimitiveComponent, OnComponentBeginOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult);
//DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams(FComponentEndOverlapSignature, UPrimitiveComponent, OnComponentEndOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex);

UCLASS()
class THIRDPERSONCPP_API ACAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAttachment();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
	void ActorAttachTo(FName InSocketName);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnEquip();
	UFUNCTION(BlueprintImplementableEvent)
	void OnUnEquip();

public:
	void OnCollision();
	void OffCollision();

private:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OnComponentBeginOverlap, UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(BlueprintAssignable)
	FAttachmentBeginOverlap OnAttachmentBeginOverlap;

	UPROPERTY(BlueprintAssignable)
	FAttachmentBeginOverlap OnAttachmentEndOverlap;

	protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USceneComponent* RootComp;

protected:
	UPROPERTY(BlueprintReadOnly)
	ACharacter* OwnerCharacter;

private:
	TArray<UShapeComponent*> ShapeComponents;
};

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProjectile.generated.h"

class USphereComponent;
class UParticleSystemComponent;
class UProjectileMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FProjectileBeginOverlap, const FHitResult&, InHitResult);

UCLASS()
class THIRDPERSONCPP_API ACProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ACProjectile();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintAssignable)
	FProjectileBeginOverlap OnProjectileBeginOverlap;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent*				SphereComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UParticleSystemComponent*		ParticleComp;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UProjectileMovementComponent*	MovementComp;

};

#include "CFeetComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

ACFeetComponent::ACFeetComponent()
{
	PrimaryActorTick.bCanEverTick = true;

	LeftSocket	= "Foot_l";
	RightSocket = "Foot_r";
	
	Additinal = 55.f;
	DrawDebugType = EDrawDebugTrace::ForOneFrame;
	FootHeight = 5.f;
}

void ACFeetComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
}

void ACFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float LeftDistance;
	Trace(LeftSocket, LeftDistance);

	float RightDistance;
	Trace(RightSocket, RightDistance);
}

void ACFeetComponent::Trace(FName InSocket, float& OutDistance)
{
	OutDistance = 0.f;

	FVector SocketLocation	= OwnerCharacter->GetMesh()->GetSocketLocation(InSocket);
	FVector Start(SocketLocation.X, SocketLocation.Y, OwnerCharacter->GetActorLocation().Z);
	
	float CapsuleHalfHeight = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	float TraceZ			= Start.Z - CapsuleHalfHeight - Additinal;

	FVector End(Start.X, Start.Y, TraceZ);

	TArray<AActor*> Ignores;
	Ignores.Add(OwnerCharacter);

	FHitResult Hit;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), true, Ignores, DrawDebugType, Hit, true);
	CheckFalse(Hit.IsValidBlockingHit);

	float DigLength = (Hit.ImpactPoint - Hit.TraceEnd).Size();
	OutDistance = (DigLength - Additinal) + FootHeight;
}
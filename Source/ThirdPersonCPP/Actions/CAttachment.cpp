#include "CAttachment.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"

ACAttachment::ACAttachment()
{
	CHelpers::CreateSceneComponent(this, &RootComp, "RootComp");

}

void ACAttachment::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	GetComponents<UShapeComponent>(ShapeComponents);
	for (const auto& Comp : ShapeComponents)
	{
		Comp->OnComponentBeginOverlap.AddDynamic(this, &ACAttachment::OnComponentBeginOverlap);
		Comp->OnComponentEndOverlap.AddDynamic(this, &ACAttachment::OnComponentEndOverlap);
	}

	Super::BeginPlay();
}

void ACAttachment::OnCollision()
{
	for (const auto& Comp : ShapeComponents)
	{
		Comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ACAttachment::OffCollision()
{
}

void ACAttachment::ActorAttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OnComponentBeginOverlap, UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OwnerCharacter == OtherActor);
	CheckTrue(OwnerCharacter->GetClass() == OtherActor->GetClass())

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OwnerCharacter && OtherActor)
	{
		OnAttachmentBeginOverlap.Broadcast(OwnerCharacter, this, OtherCharacter);
	}
}

void ACAttachment::OnComponentEndOverlap(UPrimitiveComponent* OnComponentEndOverlap, UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OwnerCharacter && OtherActor)
	{
		OnAttachmentEndOverlap.Broadcast(OwnerCharacter, this, OtherCharacter);
	}
}



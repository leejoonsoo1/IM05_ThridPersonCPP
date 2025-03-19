#include "CProjectile.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACProjectile::ACProjectile()
{
	CHelpers::CreateSceneComponent(this, &SphereComp, "SphereComp");
	CHelpers::CreateSceneComponent(this, &ParticleComp, "ParticleComp", SphereComp);

	CHelpers::CreateActorComponent(this, &MovementComp, "MovementComp");

	InitialLifeSpan = 5.f;

	MovementComp->InitialSpeed = 4000.f;
	MovementComp->MaxSpeed = 8000.f;
	MovementComp->ProjectileGravityScale = 0.f;
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ACProjectile::ProjectileBeginOverlap);
}

void ACProjectile::ProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckTrue(OtherActor == GetOwner());

	OnProjectileBeginOverlap.Broadcast(SweepResult);

	Destroy();
}

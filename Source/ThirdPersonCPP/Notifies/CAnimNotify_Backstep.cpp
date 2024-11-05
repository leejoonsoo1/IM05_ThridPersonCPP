#include "CAnimNotify_Backstep.h"
#include "Global.h"
#include "Characters/CPlayer.h"

FString UCAnimNotify_Backstep::GetNotifyName_Implementation() const
{
	return "Backstepped";
}

void UCAnimNotify_Backstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ACPlayer* Player = Cast<ACPlayer>(MeshComp->GetOwner());
	CheckNull(Player);

	Player->End_Backstep();
}

#include "CGameMode.h"
#include "Global.h"

ACGameMode::ACGameMode()
{
	CHelpers::GetClass(&DefaultPawnClass, "/Game/Player/BP_CPlayer");
	CHelpers::GetClass(&PlayerControllerClass, "/Game/Player/BP_CPlayerController");
}
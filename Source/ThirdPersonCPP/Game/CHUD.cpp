#include "CHUD.h"
#include "Global.h"
#include "Engine/Texture2D.h"
#include "Engine/Canvas.h"

ACHUD::ACHUD()
{
	CHelpers::GetAsset(&AimTextue, "/Game/Materials/T_Crosshair");
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();

	CheckFalse(bDrawAimTexture);

	CheckNull(AimTextue);

	FVector2D HalfScreenSize = FVector2D(Canvas->ClipX, Canvas->ClipY) * 0.5f;
	FVector2D HalfImageSize = FVector2D(AimTextue->GetSurfaceWidth(), AimTextue->GetSurfaceHeight()) * 0.5f;

	FVector2D Position = HalfScreenSize - HalfImageSize;

	FCanvasTileItem Item(Position, AimTextue->Resource, FLinearColor::White);
	Item.BlendMode = SE_BLEND_Translucent;

	Canvas->DrawItem(Item);

}

void ACHUD::EnableAimTexture()
{
	bDrawAimTexture = true;
}

void ACHUD::DisableAimTexture()
{
	bDrawAimTexture = false;
}

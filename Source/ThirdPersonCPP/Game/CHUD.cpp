#include "CHUD.h"
#include "Global.h"
#include "Engine/Texture2D.h"
#include "Engine/Canvas.h"

ACHUD::ACHUD()
{
	CHelpers::GetAsset(&AimTexture, "/Game/Materials/T_Crosshair");
}

void ACHUD::DrawHUD()
{
	Super::DrawHUD();
	
	CheckFalse(bDrawAimTexture);
	CheckNull(AimTexture);

	FVector2D HalfScreenSize	= FVector2D(Canvas->ClipX, Canvas->ClipY) * 0.5f;
	FVector2D HalfImageSize		= FVector2D(AimTexture->GetSurfaceWidth(), AimTexture->GetSurfaceHeight()) * 0.5f;

	FVector2D Position = HalfScreenSize - HalfImageSize;

	FCanvasTileItem Item(Position, AimTexture->Resource, FLinearColor::White);
	Item.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(Item);
}

void ACHUD::EnableAimTextTure()
{
	bDrawAimTexture = true;
}

void ACHUD::DisableAimTextTure()
{
	bDrawAimTexture = false;
}

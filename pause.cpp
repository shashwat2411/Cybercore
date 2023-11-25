#include "Pause.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"

//============================
//マクロ定義
//============================


//============================
//プロトタイプ宣言
//============================

//============================
//グローバル変数
//============================
PAUSE g_Pause;

char TextNoPause[] = "data/texture/paused.png";
static int Pause = 0;
//============================
//初期化
//============================
HRESULT InitPause()
{
	g_Pause.TextNo = LoadTexture(TextNoPause);

	g_Pause.Position.x = SCREEN_WIDTH / 2;
	g_Pause.Position.y = SCREEN_HEIGHT / 2;

	g_Pause.Size.x = 400.0f;
	g_Pause.Size.y = 70.0f;

	g_Pause.use = false;

	g_Pause.rotation = 0.0f;

	g_Pause.Offset = D3DXVECTOR2(0.0f, 0.0f);
	g_Pause.Coordinate = D3DXVECTOR2(1.0f, 1.0f);

	g_Pause.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_Pause.flip = 0;


	return S_OK;
}

void UnInitPause()
{

}

void DrawPause()
{
	DrawTriangle();
	SetWorldViewProjection2D();

	if (g_Pause.use == true)
	{
		SetTexture(g_Pause.TextNo);
		DrawSpriteColorRotate
		(
			g_Pause.Position.x,
			g_Pause.Position.y,
			g_Pause.Size.x,
			g_Pause.Size.y,
			g_Pause.rotation,
			g_Pause.color,
			&g_Pause.imageNum,
			&(g_Pause.Offset.x),
			&(g_Pause.Offset.y),
			g_Pause.Coordinate.x,
			g_Pause.Coordinate.y,
			1,
			g_Pause.flip,
			false
		);

		GetDeviceContext()->Draw(4, 0);
	}
}

void UpdatePause()
{
	if (g_Pause.use == false)
	{
		if (GetKeyboardTrigger(DIK_P))
		{
			g_Pause.use = true;
		}
	}
	else if (g_Pause.use == true)
	{
		if (GetKeyboardTrigger(DIK_P))
		{
			g_Pause.use = false;
		}
	}
}

PAUSE* GetPause()
{
	return &g_Pause;
}
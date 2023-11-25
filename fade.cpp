#include "fade.h"
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
FADE g_Fade;

static bool over = true;
bool out = false;

char TextNoFade[] = "data/texture/fade.png";
//============================
//初期化
//============================
HRESULT InitFade()
{
	{
		g_Fade.TextNo = LoadTexture(TextNoFade);

		g_Fade.Position.x = SCREEN_WIDTH / 2;
		g_Fade.Position.y = SCREEN_HEIGHT / 2;

		g_Fade.Size.x = SCREEN_WIDTH;
		g_Fade.Size.y = SCREEN_HEIGHT;

		g_Fade.use = true;

		g_Fade.rotation = 0.0f;

		g_Fade.Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Fade.Coordinate = D3DXVECTOR2(1.0f, 1.0f);

		g_Fade.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		g_Fade.flip = 0;
	}


	return S_OK;
}

//============================
//終了処理
//============================
void UnInitFade()
{

}


//============================
//描画処理
//============================
void DrawFade()
{
	DrawTriangle();
	SetWorldViewProjection2D();

	if (g_Fade.use == true)
	{
		SetTexture(g_Fade.TextNo);
		DrawSpriteColorRotate
		(
			g_Fade.Position.x, 
			g_Fade.Position.y, 
			g_Fade.Size.x, 
			g_Fade.Size.y, 
			g_Fade.rotation, 
			g_Fade.color, 
			&g_Fade.imageNum, 
			&(g_Fade.Offset.x), 
			&(g_Fade.Offset.y), 
			g_Fade.Coordinate.x, 
			g_Fade.Coordinate.y, 
			1, 
			g_Fade.flip, 
			false
		);

		GetDeviceContext()->Draw(4, 0);
	}
}

//============================
//更新処理
//============================
void UpdateFade()
{
	if (g_Fade.use == true)
	{
		over = false;
		if (g_Fade.type == FADEIN)
		{
			g_Fade.color.a -= FADE_SPEED;
			if (g_Fade.color.a <= 0.0f)
			{
				g_Fade.color.a = 0;
				over = true;
			}
		}
		if (g_Fade.type == FADEOUT)
		{
			g_Fade.color.a += FADE_SPEED;
			if (g_Fade.color.a >= 1.0f)
			{
				g_Fade.type = NONE;
				over = true;
			}
		}
		if (g_Fade.type == NONE)
		{
			g_Fade.color.a = 0.0f;
		}
	}
}


void SetFade(TYPE type)
{
	if (g_Fade.use == true)
	{
		g_Fade.type = type;

		if (g_Fade.type == FADEIN) { g_Fade.color.a = 1.0f; }
		else if (g_Fade.type == FADEOUT) { g_Fade.color.a = 0.0f; }
	}
}

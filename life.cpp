#include "life.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

//============================
//マクロ定義
//============================
#define YOKO_NUM 1
#define TATE_NUM 1
#define WHOLE_NUM (int)YOKO_NUM * TATE_NUM
#define YOKO (float)1.0f / YOKO_NUM
#define TATE (float)1.0f / TATE_NUM

//============================
//プロトタイプ宣言
//============================

//============================
//グローバル変数
//============================
static LIFE g_Life[LIFEPOINTS];
PLAYER* Player1;
static int Life = 0;

char TextNoLife[] = "data/texture/heart.png";

//============================
//初期化
//============================
HRESULT InitLife()
{
	Player1 = GetPlayer();
	//プレーヤー構造体の初期化
	for (int i = 0; i < LIFEPOINTS; i++)
	{
		g_Life[i].Life = 0;

		g_Life[i].TextNo = LoadTexture(TextNoLife);

		g_Life[i].Position.x = 30.0f + i * 35;
		g_Life[i].Position.y = 35.0f;

		g_Life[i].Size.x = 30.0f;
		g_Life[i].Size.y = 30.0f;

		g_Life[i].use = true;

		g_Life[i].rotation = 0.0f;

		g_Life[i].Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Life[i].Coordinate = D3DXVECTOR2(YOKO, TATE);

		g_Life[i].color = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		g_Life[i].flip = 0;
	}

	Life = Player1->HP;

	return S_OK;
}

void UnInitLife()
{

}

void DrawLife()
{
	DrawTriangle();
	SetWorldViewProjection2D();

	for (int i = 0; i < LIFEPOINTS; i++)
	{
		if (g_Life[i].use == true)
		{
			SetTexture(g_Life[0].TextNo);
			DrawSpriteColorRotate
			(
				g_Life[i].Position.x,
				g_Life[i].Position.y,
				g_Life[i].Size.x,
				g_Life[i].Size.y,
				g_Life[i].rotation,
				g_Life[i].color,
				&g_Life[i].imageNum,
				&(g_Life[i].Offset.x),
				&(g_Life[i].Offset.y),
				g_Life[i].Coordinate.x,
				g_Life[i].Coordinate.y,
				YOKO_NUM,
				g_Life[i].flip,
				false
			);

			GetDeviceContext()->Draw(4, 0);
		}
	}
}

void UpdateLife()
{
	Player1 = GetPlayer();
	for (int i = LIFEPOINTS-1; i >= 0; i--)
	{
		if (Player1->HP == i)
		{
			g_Life[i].color = D3DXCOLOR(0.42f, 0.16f, 0.1f, 1.0f);
		}
	}
}

LIFE* GetLife()
{
	return &g_Life[0];
}


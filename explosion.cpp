#include "explosion.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"

#include "sound.h"

//============================
//マクロ定義
//============================
#define EXPLOSION_SIZE_X 75.0f
#define EXPLOSION_SIZE_Y 75.0f

#define YOKO_NUM 8
#define TATE_NUM 1
#define WHOLE_NUM (int)YOKO_NUM * TATE_NUM
#define YOKO (float)1.0f / YOKO_NUM
#define TATE 1.0f
//============================
//プロトタイプ宣言
//============================

//============================
//グローバル変数
//============================
static EXPLOSION g_Explosion[EXPLOSION_MAX];

char TextNoExplosion[] = "data/texture/explosion000.png";

int ExplosionSoundNo;

int temp;
int countExplosion = 0;
//============================
//初期化
//============================
HRESULT InitExplosion()
{
	temp = LoadTexture(TextNoExplosion);
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].TextNo = LoadTexture(TextNoExplosion);

		g_Explosion[i].Position.x = SCREEN_WIDTH / 2;
		g_Explosion[i].Position.y = SCREEN_HEIGHT / 2;

		g_Explosion[i].Size.x = EXPLOSION_SIZE_X;
		g_Explosion[i].Size.y = EXPLOSION_SIZE_Y;

		g_Explosion[i].use = false;

		g_Explosion[i].imageNum = 0;
		g_Explosion[i].rotation = 0.0f;


		g_Explosion[i].Offset = D3DXVECTOR2(0.0f, 0.0f);
		//g_Explosion[i].Coordinate = D3DXVECTOR2(YOKO, TATE);

		g_Explosion[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_Explosion[i].flip = 0;

	}

	char filename[] = "data\\SE\\bomb000.wav";
	ExplosionSoundNo = LoadSound(filename);


	return S_OK;
}

void UnInitExplosion()
{
}

void DrawExplosion()
{
	DrawTriangle();
	SetWorldViewProjection2D();

	
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].use == true)
		{
			SetTexture(g_Explosion[i].TextNo);
			SetBlendState(BLEND_MODE_ADD);
			DrawSpriteColorRotate
			(
				g_Explosion[i].Position.x,
				g_Explosion[i].Position.y,
				g_Explosion[i].Size.x,
				g_Explosion[i].Size.y,
				g_Explosion[i].rotation,
				g_Explosion[i].color,
				&g_Explosion[i].imageNum,
				&(g_Explosion[i].Offset.x),
				&(g_Explosion[i].Offset.y),
				YOKO,
				1.0f,
				YOKO_NUM,
				g_Explosion[i].flip,
				false
			);

			//SpriteSheet(&g_Explosion[i].Offset.x, &g_Explosion[i].Offset.y, &g_Explosion[i].imageNum, YOKO_NUM, g_Explosion[i].Coordinate.x, g_Explosion[i].Coordinate.y, countExplosion, 5);

			if (countExplosion % 5 == 0)
			{
				g_Explosion[i].Offset.x = ((g_Explosion[i].imageNum) % YOKO_NUM) * YOKO;
				g_Explosion[i].imageNum += 1;
			}

			GetDeviceContext()->Draw(4, 0);
			SetBlendState(BLEND_MODE_ALPHABLEND);
		}
	}
}

void UpdateExplosion()
{
	countExplosion++;
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].use == true)
		{
			if (g_Explosion[i].Offset.x >= 1.0f - YOKO)
			{
				g_Explosion[i].use = false;
				g_Explosion[i].Offset.x = 0.0f;
				g_Explosion[i].Offset.y = 0.0f;
				g_Explosion[i].imageNum = 0;
			}
		}
	}
}

EXPLOSION * GetExplosion()
{
	return &g_Explosion[0];
}

void SetExplosion(D3DXVECTOR2 Position, D3DXVECTOR2 Size, D3DXCOLOR Color, float Volume)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].use == false)
		{
			g_Explosion[i].Position = Position;
			g_Explosion[i].Size = Size;
			g_Explosion[i].color = Color;
			g_Explosion[i].imageNum = 0;
			g_Explosion[i].Offset.x = 0.0f;
			g_Explosion[i].Offset.y = 0.0f;
			g_Explosion[i].use = true;

			SetVolume(ExplosionSoundNo, Volume);
			PlaySoundInGame(ExplosionSoundNo, 0);

			return;
		}
	}
}
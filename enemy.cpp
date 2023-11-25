#include "enemy.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "player.h"
#include "explosion.h"
#include <stdlib.h>

//============================
//マクロ定義
//============================
#define ENEMY_SIZE_X 70.0f
#define ENEMY_SIZE_Y 50.0f

#define ENEMY_MOVE_SPACE 100.0f


//============================
//プロトタイプ宣言
//============================

//============================
//グローバル変数
//============================
static ENEMY g_Enemy[ENEMY_MAX];

D3DXVECTOR2 Temp1[ENEMY_MAX];
D3DXVECTOR2 Temp2[ENEMY_MAX];

int c = 0;
int numH = 0, numV = 0;
static int count = 0;

char TextNoEnemy[] = "data/texture/enemy.png";
//============================
//初期化
//============================
HRESULT InitEnemy()
{
	g_Enemy[0].TextNo = LoadTexture(TextNoEnemy);

	//プレーヤー構造体の初期化
	for (int i = 0; i < ENEMY_NUMBER_MAX; i++)
	{
		int random = rand() % 2;

		g_Enemy[i].Position.x = 0.0f;
		g_Enemy[i].Position.y = 0.0f;

		g_Enemy[i].Size.x = ENEMY_SIZE_X;
		g_Enemy[i].Size.y = ENEMY_SIZE_Y;

		g_Enemy[i].Speed.x = 0.0f;
		g_Enemy[i].Speed.y = 0.0f;

		g_Enemy[i].use = false;
		g_Enemy[i].blink = false;

		g_Enemy[i].rotation = 0.0f;

		g_Enemy[i].Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Enemy[i].Coordinate = D3DXVECTOR2(1.0f, 1.0f);

		g_Enemy[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_Enemy[i].flip = 0;
		g_Enemy[i].HP = 3;
		g_Enemy[i].frameWait = (i + 1) * SECONDS;
	}

	return S_OK;
}

//============================
//終了処理
//============================
void UnInitEnemy()
{

}

//============================
//描画処理
//============================
void DrawEnemy()
{
	DrawTriangle();
	SetWorldViewProjection2D();

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true)
		{
			SetTexture(g_Enemy[0].TextNo);
			SetBlendState(BLEND_MODE_ADD);
			DrawSpriteColorRotate
			(
				g_Enemy[i].Position.x,
				g_Enemy[i].Position.y,
				g_Enemy[i].Size.x,
				g_Enemy[i].Size.y,
				g_Enemy[i].rotation,
				g_Enemy[i].color,
				&g_Enemy[i].imageNum,
				&(g_Enemy[i].Offset.x),
				&(g_Enemy[i].Offset.y),
				g_Enemy[i].Coordinate.x,
				g_Enemy[i].Coordinate.y,
				1,
				g_Enemy[i].flip,
				false
			);

			GetDeviceContext()->Draw(4, 0);

			SetBlendState(BLEND_MODE_ALPHABLEND);
		}
	}
}

//============================
//更新処理
//============================
void UpdateEnemy()
{
	count++;
	
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].use == true && g_Enemy[i].frameWait <= 0.0f)
		{
			//ENEMY SHOOT
			if (count % 120 == 0)
			{
				PLAYER* Player = GetPlayer();
				SetEnemyBullet(g_Enemy[i].Position, Player->Position);
			}

			//Enemy Rotation towards the player
			{
				PLAYER* PlayerRotation = GetPlayer();
				float X = PlayerRotation->Position.x;
				float Y = PlayerRotation->Position.y;
				float corrector = 90;
				float base = (Y - g_Enemy[i].Position.y);
				float height = (X - g_Enemy[i].Position.x);

				g_Enemy[i].rotation = (atanf(base / height) * 180 / 3.14159);

				if (PlayerRotation->Position.x < g_Enemy[i].Position.x) { corrector = 90; }
				else { corrector = -90; }

				g_Enemy[i].rotation += corrector;
			}

			//プレーヤーを追いかける処理
			{
				D3DXVECTOR2 temp;
				PLAYER* Player = GetPlayer();
				temp = Player->Position - g_Enemy[i].Position;
				D3DXVec2Normalize(&temp, &temp);
				temp *= 0.6f;

				g_Enemy[i].Speed = temp;
				g_Enemy[i].Position += g_Enemy[i].Speed;
			}


			if (g_Enemy[i].HP <= 0)
			{
				g_Enemy[i].use = false;
				g_Enemy[i].HP = 3;
				g_Enemy[i].frameWait = SECONDS;

				SetExplosion(g_Enemy[i].Position, D3DXVECTOR2(100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 0.1f);
			}

			if (g_Enemy[i].blink == true) { c++; }

			if (c > 10)
			{
				g_Enemy[i].color.g = 1.0f;
				g_Enemy[i].color.b = 1.0f;
				g_Enemy[i].blink = false;
				c = 0;
			}
		}
		else
		{
			g_Enemy[i].frameWait -= 1.0f;
			if (g_Enemy[i].frameWait <= 0.0f)
			{
				D3DXVECTOR2 random;

				g_Enemy[i].frameWait = 0.0f;

				static float x = 0, y = 0;
				x = generateRandom(-ENEMY_HORIZONTAL * 2, SCREEN_WIDTH - ENEMY_HORIZONTAL);
				y = generateRandom(-ENEMY_VERTICAL * 2, SCREEN_HEIGHT - ENEMY_VERTICAL);
				random = D3DXVECTOR2(x, y);

				SetEnemy(g_Enemy, random);
			}
		}
	}
}

//============================
//構造体の戦闘ポインタを返す
//============================
ENEMY* GetEnemy()
{
	return &g_Enemy[0];
}

void SetEnemy(ENEMY* Enemy, D3DXVECTOR2 Position)
{
	for (int i = 0; i < ENEMY_NUMBER_MAX; i++)
	{
		if (Enemy[i].use == false)
		{
			Enemy[i].Position = Position;
			Enemy[i].use = true;
			return;
		}
	}
}

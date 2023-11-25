#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "screen.h"
#include "sound.h"
#include "life.h"
#include "explosion.h"

//============================
//マクロ定義
//============================
#define YOKO_NUM 1
#define TATE_NUM 1
#define WHOLE_NUM (int)YOKO_NUM * TATE_NUM
#define YOKO (float)1.0f / YOKO_NUM
#define TATE (float)1.0f / TATE_NUM

#define PLAYER_SIZE_X 107.14f
#define PLAYER_SIZE_Y 50.0f

#define PLAYER_SPEED 5.0f

#define INVINCIBLE_COUNTER 60
//============================
//プロトタイプ宣言
//============================

//============================
//グローバル変数
//============================
static PLAYER g_Player;

static int counter = 0;

char TextNoPlayer[] = "data/texture/player.png";
//============================
//初期化
//============================
HRESULT InitPlayer()
{
	//プレーヤー構造体の初期化
	{
		g_Player.TextNo = LoadTexture(TextNoPlayer);

		g_Player.Position.x = SCREEN_WIDTH / 2;
		g_Player.Position.y = SCREEN_HEIGHT / 2 + 200;

		g_Player.Size.x = PLAYER_SIZE_X;
		g_Player.Size.y = PLAYER_SIZE_Y;

		g_Player.use = true;
		g_Player.animate = false;
		g_Player.invincible = false;

		g_Player.rotation = 0.0f;

		g_Player.Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Player.Coordinate = D3DXVECTOR2(YOKO, TATE);

		g_Player.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_Player.flip = 0;
		g_Player.HP = LIFEPOINTS;
		g_Player.invCounter = INVINCIBLE_COUNTER;

		char enemy[] = "data\\SE\\lifeLose.wav";
		g_Player.sound = LoadSound(enemy);
	}	

	return S_OK;
}

//============================
//終了処理
//============================
void UnInitPlayer()
{
	
}

//============================
//描画処理
//============================
void DrawPlayer()
{
	DrawTriangle();
	SetWorldViewProjection2D();


	int yokoNum = 0;
	if (g_Player.Offset.x <= 0.0f) { yokoNum = 1.0f; }
	else { yokoNum = 1.0f / g_Player.Offset.x; }

	if (g_Player.use == true)
	{
		SetTexture(g_Player.TextNo);
		DrawSpriteColorRotate
		(
			g_Player.Position.x,
			g_Player.Position.y,
			g_Player.Size.x,
			g_Player.Size.y,
			g_Player.rotation,
			g_Player.color,
			&g_Player.imageNum,
			&(g_Player.Offset.x),
			&(g_Player.Offset.y),
			g_Player.Coordinate.x,
			g_Player.Coordinate.y,
			yokoNum,
			g_Player.flip,
			g_Player.animate
		);

		GetDeviceContext()->Draw(4, 0);
	}
}

//============================
//更新処理
//============================
void UpdatePlayer()
{
	if (g_Player.use == true)
	{
		D3DXVECTOR2 move = D3DXVECTOR2(0.0f, 0.0f);
		//入力処理
		counter += 1;

		if (counter % 8 == 0) { if (GetKeyboardPress(DIK_SPACE)) { SetBullet(); } }

		if (GetKeyboardPress(DIK_UP)) { move.y += -PLAYER_SPEED; }
		else if (GetKeyboardPress(DIK_DOWN)) { move.y += PLAYER_SPEED; }
		else if (GetKeyboardPress(DIK_RIGHT)) { move.x += PLAYER_SPEED; }
		else if (GetKeyboardPress(DIK_LEFT)) { move.x += -PLAYER_SPEED; }

		//D3DXVec2Normalize(&move, &move);
		g_Player.Position += move;	
		
		if (GetKeyboardPress(DIK_A)) { g_Player.rotation += -5.0f; }
		else if (GetKeyboardPress(DIK_D)) { g_Player.rotation += 5.0f; }


		//無敵時間
		if (g_Player.invincible == true)
		{
			if (g_Player.invCounter % 12 == 0) { g_Player.color.a = 1.0f; }
			else if (g_Player.invCounter % 12 == 6) { g_Player.color.a = 0.0f; }

			g_Player.invCounter -= 1;

			if (g_Player.invCounter <= 0)
			{
				g_Player.invCounter = INVINCIBLE_COUNTER;
				g_Player.invincible = false;
				g_Player.color.a = 1.0f;
			}
		}


		//死ぬ処理
		if (g_Player.HP <= 0)
		{
			g_Player.HP = 0;
			g_Player.use = false;

			SetExplosion(g_Player.Position, D3DXVECTOR2(200.0f, 200.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f), 0.3f);
		}


		//枠作成処理
		if (g_Player.Position.x > SCREEN_WIDTH) { g_Player.Position.x = SCREEN_WIDTH; }
		if (g_Player.Position.x < 0) { g_Player.Position.x = 0; }
		if (g_Player.Position.y > SCREEN_HEIGHT) { g_Player.Position.y = SCREEN_HEIGHT; }
		if (g_Player.Position.y < 0) { g_Player.Position.y = 0; }
	}
}

//============================
//構造体の戦闘ポインタを返す
//============================
PLAYER* GetPlayer()
{
	return &g_Player;
}

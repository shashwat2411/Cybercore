#include "score.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"

//============================
//マクロ定義
//============================
#define SCORE_SIZE_X 30.0f
#define SCORE_SIZE_Y 40.0f

#define YOKO_NUM 10
#define TATE_NUM 1
#define WHOLE_NUM (int)YOKO_NUM * TATE_NUM
#define YOKO (float)1.0f / YOKO_NUM
#define TATE (float)1.0f / TATE_NUM

#define FRAME 5

//============================
//プロトタイプ宣言
//============================

//============================
//グローバル変数
//============================
static SCORE g_Score[DIGITS];

char TextNoScore[] = "data/texture/number.png";
static int Score = 0;
//============================
//初期化
//============================
HRESULT InitScore()
{
	//プレーヤー構造体の初期化
	for (int i = 0; i < DIGITS; i++)
	{
		g_Score[i].Score = 0;

		g_Score[i].TextNo = LoadTexture(TextNoScore);

		g_Score[i].Position.x = 930.0f - i * 20;
		g_Score[i].Position.y = 30.0f;

		g_Score[i].Size.x = SCORE_SIZE_X;
		g_Score[i].Size.y = SCORE_SIZE_Y;

		g_Score[i].use = true;

		g_Score[i].rotation = 0.0f;

		g_Score[i].Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Score[i].Coordinate = D3DXVECTOR2(YOKO, TATE);

		g_Score[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_Score[i].flip = 0;
	}

	Score = 0;

	return S_OK;
}

void UnInitScore()
{

}

void DrawScore()
{
	DrawTriangle();
	SetWorldViewProjection2D();

	for (int i = 0; i < DIGITS; i++)
	{
		if (g_Score[i].use == true)
		{
			SetTexture(g_Score[0].TextNo);
			DrawSpriteColorRotate
			(
				g_Score[i].Position.x, 
				g_Score[i].Position.y, 
				g_Score[i].Size.x, 
				g_Score[i].Size.y, 
				g_Score[i].rotation, 
				g_Score[i].color, 
				&g_Score[i].imageNum, 
				&(g_Score[i].Offset.x), 
				&(g_Score[i].Offset.y), 
				g_Score[i].Coordinate.x, 
				g_Score[i].Coordinate.y, 
				YOKO_NUM, 
				g_Score[i].flip, 
				false
			);

			GetDeviceContext()->Draw(4, 0);
		}
	}
}

void UpdateScore()
{
	if (Score < 0) { Score = 0; }
	if (Score > 999) { Score = 999; }

	g_Score[2].Score = Score / 100;
	g_Score[1].Score = Score % 100 / 10;
	g_Score[0].Score = Score % 10;
	
	g_Score[2].imageNum = g_Score[2].Score;
	g_Score[1].imageNum = g_Score[1].Score;
	g_Score[0].imageNum = g_Score[0].Score;

	for (int i = 0; i < DIGITS; i++)
	{
		g_Score[i].Offset.x = ((g_Score[i].imageNum) % YOKO_NUM) * g_Score[i].Coordinate.x;
	}
}

SCORE * GetScore()
{
	return &g_Score[0];
}

int* GetRealScore()
{
	return &Score;
}

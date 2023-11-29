#include "result.h"
#include "input.h"
#include "sprite.h"
#include "screen.h"
#include "texture.h"
#include "fade.h"
#include "score.h"

#include "sound.h"

struct RESULT
{
	D3DXVECTOR2 Position;
	D3DXVECTOR2 Size;
	D3DXCOLOR Color;
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;
	int imageNum;
	int TextNo;
	bool animate;
	bool use;
};

RESULT g_Result;
RESULT g_ResultText;
RESULT g_Press;
SCORE* ScoreResult;

bool nextResult = false;
int countResult = 0;
float faderR = 0.006f;

int ResultSoundNo;
int ButtonSoundR;

char TextNoResult[] = "data/texture/resultBG.png";
char TextNoResultText[] = "data/texture/result.png";
char TextNoPress[] = "data/texture/pressEnter.png";

HRESULT InitResult()
{
	{
		g_Result.TextNo = LoadTexture(TextNoResult);
		g_Result.imageNum = 0;
		g_Result.Position = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		g_Result.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		g_Result.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Result.Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Result.Coordinate = D3DXVECTOR2(1.0f, 1.0f);
		g_Result.use = true;
		g_Result.animate = false;
	}

	{
		g_ResultText.TextNo = LoadTexture(TextNoResultText);
		g_ResultText.imageNum = 0;
		g_ResultText.Position = D3DXVECTOR2(SCREEN_WIDTH / 2, 120.0f);
		g_ResultText.Size = D3DXVECTOR2(400.0f, 100.0f);
		g_ResultText.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_ResultText.Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_ResultText.Coordinate = D3DXVECTOR2(1.0f, 1.0f);
		g_ResultText.use = true;
		g_ResultText.animate = false;
	}

	{
		g_Press.TextNo = LoadTexture(TextNoPress);
		g_Press.imageNum = 0;
		g_Press.Position = D3DXVECTOR2(SCREEN_WIDTH / 2, 320.0f);
		g_Press.Size = D3DXVECTOR2(180.0f, 30.0f);
		g_Press.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Press.Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Press.Coordinate = D3DXVECTOR2(1.0f, 1.0f);
		g_Press.use = true;
		g_Press.animate = false;
	}

	ScoreResult = GetScore();
	for (int i = 0; i < DIGITS; i++)
	{
		ScoreResult[i].Position = D3DXVECTOR2(SCREEN_WIDTH / 2 + 20 - i * 20, SCREEN_HEIGHT / 2);
	}

	char button[] = "data\\SE\\button.wav";
	ButtonSoundR = LoadSound(button);

	SetFade(FADEIN);

	return S_OK;

}

void UnInitResult()
{
	UnInitScore();
	StopSoundAll();
}

void DrawResult()
{
	DrawTriangle();
	SetWorldViewProjection2D();

	if (g_Result.use == true)
	{
		SetTexture(g_Result.TextNo);
		DrawSpriteColorRotate
		(
			g_Result.Position.x, 
			g_Result.Position.y, 
			g_Result.Size.x, 
			g_Result.Size.y, 
			0.0f, 
			g_Result.Color, 
			&g_Result.imageNum, 
			&g_Result.Offset.x, 
			&g_Result.Offset.y, 
			g_Result.Coordinate.x, 
			g_Result.Coordinate.y, 
			1.0f, 
			5, 
			g_Result.animate
		);

		GetDeviceContext()->Draw(4, 0);
	}

	if (g_ResultText.use == true)
	{
		SetTexture(g_ResultText.TextNo);
		DrawSpriteColorRotate
		(
			g_ResultText.Position.x,
			g_ResultText.Position.y,
			g_ResultText.Size.x,
			g_ResultText.Size.y,
			0.0f,
			g_ResultText.Color,
			&g_ResultText.imageNum,
			&g_ResultText.Offset.x,
			&g_ResultText.Offset.y,
			g_ResultText.Coordinate.x,
			g_ResultText.Coordinate.y,
			1.0f,
			5,
			g_ResultText.animate
		);

		GetDeviceContext()->Draw(4, 0);
	}

	if (g_Press.use == true)
	{
		SetTexture(g_Press.TextNo);
		DrawSpriteColorRotate
		(
			g_Press.Position.x,
			g_Press.Position.y,
			g_Press.Size.x,
			g_Press.Size.y,
			0.0f,
			g_Press.Color,
			&g_Press.imageNum,
			&g_Press.Offset.x,
			&g_Press.Offset.y,
			g_Press.Coordinate.x,
			g_Press.Coordinate.y,
			1.0f,
			5,
			g_Press.animate
		);

		GetDeviceContext()->Draw(4, 0);
	}

	DrawScore();
}

void UpdateResult()
{
	UpdateScore();

	if (g_Press.use == true)
	{
		if (g_Press.Color.a >= 1.0f || g_Press.Color.a <= 0.0f)
		{
			if (g_Press.Color.a >= 1.0f) { g_Press.Color.a = 1.0f; }
			else if (g_Press.Color.a <= 0.0f) { g_Press.Color.a = 0.0f; }

			faderR *= -1;
		}
		g_Press.Color.a += faderR;
	}

	if (GetKeyboardPress(DIK_RETURN))// && go == false)
	{
		PlaySoundInGame(ButtonSoundR, 0);
		SetFade(FADEOUT);
		nextResult = true;
	}

	if (nextResult == true)
	{
		countResult += 1;
		if (countResult >= FADE_WAIT)
		{
			SetScene(SCENE_MAIN);
			nextResult = false;
			countResult = 0;
		}
	}
}

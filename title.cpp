#include "title.h"
#include "input.h"
#include "sprite.h"
#include "screen.h"
#include "texture.h"
#include "fade.h"

#include "sound.h"

struct TITLE
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

TITLE g_Title;
TITLE g_PressA;
TITLE g_TitleText;

bool next = false;
int countTitle = 0;
float fader = 0.006f;

int TitleSoundNo;
int ButtonSound;

char TextNoTitle[] = "data/texture/title.png";
char TextNoPressA[] = "data/texture/pressEnter.png";
char TextNoTitleText[] = "data/texture/Cybercore.png";

HRESULT InitTitle()
{
	{
		g_Title.TextNo = LoadTexture(TextNoTitle);
		g_Title.imageNum = 0;
		g_Title.Position = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		g_Title.Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
		g_Title.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Title.Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Title.Coordinate = D3DXVECTOR2(1.0f, 1.0f);
		g_Title.use = true;
		g_Title.animate = false;
	}

	{
		g_PressA.TextNo = LoadTexture(TextNoPressA);
		g_PressA.imageNum = 0;
		g_PressA.Position = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		g_PressA.Size = D3DXVECTOR2(300.0f, 50.0f);
		g_PressA.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_PressA.Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_PressA.Coordinate = D3DXVECTOR2(1.0f, 1.0f);
		g_PressA.use = true;
		g_PressA.animate = false;
	}

	{
		g_TitleText.TextNo = LoadTexture(TextNoTitleText);
		g_TitleText.imageNum = 0;
		g_TitleText.Position = D3DXVECTOR2(SCREEN_WIDTH / 2, 120.0f);
		g_TitleText.Size = D3DXVECTOR2(500.0f, 175.0f);
		g_TitleText.Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_TitleText.Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_TitleText.Coordinate = D3DXVECTOR2(1.0f, 1.0f);
		g_TitleText.use = true;
		g_TitleText.animate = false;
	}

	char filename[] = "data\\BGM\\sample000.wav";
	char button[] = "data\\SE\\button.wav";
	TitleSoundNo = LoadSound(filename);
	ButtonSound = LoadSound(button);

	SetFade(FADEIN);
	SetVolume(TitleSoundNo, 0.2f);
	PlaySoundInGame(TitleSoundNo, -1);

	return S_OK;
}

void UnInitTitle()
{
	StopSoundAll();
}

void DrawTitle()
{
	DrawTriangle();
	SetWorldViewProjection2D();

	if (g_Title.use == true)
	{
		SetTexture(g_Title.TextNo);
		DrawSpriteColorRotate
		(
			g_Title.Position.x, 
			g_Title.Position.y, 
			g_Title.Size.x, 
			g_Title.Size.y, 
			0.0f, 
			g_Title.Color, 
			&g_Title.imageNum, 
			&g_Title.Offset.x, 
			&g_Title.Offset.y, 
			g_Title.Coordinate.x, 
			g_Title.Coordinate.y, 
			1.0f, 
			5, 
			g_Title.animate
		);

		GetDeviceContext()->Draw(4, 0);
	}

	if (g_PressA.use == true)
	{
		SetTexture(g_PressA.TextNo);
		DrawSpriteColorRotate
		(
			g_PressA.Position.x,
			g_PressA.Position.y,
			g_PressA.Size.x,
			g_PressA.Size.y,
			0.0f,
			g_PressA.Color,
			&g_PressA.imageNum,
			&g_PressA.Offset.x,
			&g_PressA.Offset.y,
			g_PressA.Coordinate.x,
			g_PressA.Coordinate.y,
			1.0f,
			5,
			g_PressA.animate
		);

		GetDeviceContext()->Draw(4, 0);
	}
	
	if (g_TitleText.use == true)
	{
		SetTexture(g_TitleText.TextNo);
		DrawSpriteColorRotate
		(
			g_TitleText.Position.x,
			g_TitleText.Position.y,
			g_TitleText.Size.x,
			g_TitleText.Size.y,
			0.0f,
			g_TitleText.Color,
			&g_TitleText.imageNum,
			&g_TitleText.Offset.x,
			&g_TitleText.Offset.y,
			g_TitleText.Coordinate.x,
			g_TitleText.Coordinate.y,
			1.0f,
			5,
			g_TitleText.animate
		);

		GetDeviceContext()->Draw(4, 0);
	}
}

void UpdateTitle()
{
	if (g_PressA.use == true)
	{
		if (g_PressA.Color.a >= 1.0f || g_PressA.Color.a <= 0.0f)
		{
			if (g_PressA.Color.a >= 1.0f) { g_PressA.Color.a = 1.0f; }
			else if (g_PressA.Color.a <= 0.0f) { g_PressA.Color.a = 0.0f; }

			fader *= -1;
		}
		g_PressA.Color.a += fader;
	}
	
	if (GetKeyboardPress(DIK_RETURN))// && go == false)
	{
		PlaySoundInGame(ButtonSound, 0);
		SetFade(FADEOUT);
		next = true;
	}

	if (next == true)
	{
		countTitle += 1;
		if (countTitle >= FADE_WAIT)
		{
			SetScene(SCENE_GAME);
			next = false;
			countTitle = 0;
		}
	}
}

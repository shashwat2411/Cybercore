#include "game.h"
#include "player.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "score.h"
#include "explosion.h"
#include "life.h"
#include "collision.h"
#include "fade.h"
#include "input.h"
#include "screen.h"
#include "pause.h"

#include "sound.h"

int GameSoundNo;
bool nextGame = false;
int countGame = 0;

int LoseSound;

PLAYER* P;
PAUSE* Pause;

HRESULT InitGame()
{
	InitBG();
	InitPlayer();
	InitBullet();
	InitEnemy();
	InitScore();
	InitLife();
	InitExplosion();
	InitPause();

	char filename[] = "data\\BGM\\sample001.wav";
	char lose[] = "data\\SE\\lose.wav";
	GameSoundNo = LoadSound(filename);
	LoseSound = LoadSound(lose);

	SetVolume(GameSoundNo, 0.1);
	PlaySound(GameSoundNo, -1);

	SetFade(FADEIN);

	P = GetPlayer();
	P->color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	return S_OK;
}

void UnInitGame()
{
	UnInitBG();
	UnInitPlayer();
	UnInitBullet();
	UnInitEnemy();
	UnInitScore();
	UnInitLife();
	UnInitExplosion();
	UnInitPause();

	StopSound(GameSoundNo);
}

void DrawGame()
{
	DrawBG();
	DrawBullet();
	DrawEnemy();
	DrawPlayer();
	DrawExplosion();
	DrawScore();
	DrawLife();
	DrawPause();
}

void UpdateGame()
{
	Pause = GetPause();

	if (Pause->use == false)
	{
		UpdateCollision();
		UpdateBG();
		UpdatePlayer();
		UpdateExplosion();
		UpdateBullet();
		UpdateEnemy();
		UpdateScore();
		UpdateLife();
	}
	UpdatePause();

	P = GetPlayer();
	if (P->use == false)
	{
		SetVolume(LoseSound, 0.5);
		PlaySound(LoseSound, 0);

		SetFade(FADEOUT);
		nextGame = true;
	}

	if (nextGame == true)
	{
		countGame += 1;
		if (countGame >= FADE_WAIT)
		{
			SetScene(SCENE_RESULT);
			nextGame = false;
			countGame = 0;
		}
	}
}

#pragma once
#include "main.h"
#include "renderer.h"

#define FADE_SPEED 0.05f
#define FADE_WAIT (1.0f / FADE_SPEED)

enum TYPE
{
	FADEIN = 1,
	FADEOUT = 2,
	NONE = 0
};

struct FADE
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//大きさ
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//テクスチャ番号
	int type;

	float rotation;	//回転角度

	bool use;	//構造体使用中フラグ
};

HRESULT InitFade();
void UnInitFade();
void UpdateFade();
void DrawFade();

void SetFade(TYPE type);
#pragma once

#include "main.h"
#include "renderer.h"

//============================
//マクロ定義
//============================
#define ENEMY_NUMBER_MAX 100

#define ENEMY_HORIZONTAL 8
#define ENEMY_VERTICAL 3

#define ENEMY_MAX 10

#define DISTANCE_X 100
#define DISTANCE_Y 80

#define SECONDS 100.0f
//============================
//構造体定義
//============================
struct ENEMY
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//大きさ
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;
	D3DXVECTOR2 Speed;

	D3DXCOLOR color;

	int imageNum;	
	int flip;
	int TextNo;	//テクスチャ番号
	int HP;

	float rotation;	//回転角度
	float frameWait;

	bool use;	//構造体使用中フラグ
	bool blink;
};

//============================
//プロトタイプ宣言
//============================
HRESULT InitEnemy();
void UnInitEnemy();
void DrawEnemy();
void UpdateEnemy();

ENEMY* GetEnemy();

void SetEnemy(ENEMY* Enemy, D3DXVECTOR2 Position);
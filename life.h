#pragma once

#include "main.h"
#include "renderer.h"

//============================
//マクロ定義
//============================
#define LIFEPOINTS 5

//============================
//構造体定義
//============================
struct LIFE
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//大きさ
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//テクスチャ番号
	int Life;

	float rotation;	//回転角度

	bool use;	//構造体使用中フラグ
};

//============================
//プロトタイプ宣言
//============================
HRESULT InitLife();	//初期化
void UnInitLife();	//終了処理
void DrawLife();	//描写処理
void UpdateLife();	//更新処理

LIFE* GetLife();	//構造体の先頭のポインタを返す
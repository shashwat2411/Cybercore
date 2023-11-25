#pragma once

#include "main.h"
#include "renderer.h"

//============================
//マクロ定義
//============================
#define DIGITS 3

//============================
//構造体定義
//============================
struct SCORE
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//大きさ
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//テクスチャ番号
	int Score;

	float rotation;	//回転角度

	bool use;	//構造体使用中フラグ
};

//============================
//プロトタイプ宣言
//============================
HRESULT InitScore();	//初期化
void UnInitScore();	//終了処理
void DrawScore();	//描写処理
void UpdateScore();	//更新処理

SCORE* GetScore();	//構造体の先頭のポインタを返す
int* GetRealScore();
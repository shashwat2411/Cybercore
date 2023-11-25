#pragma once

#include "main.h"
#include "renderer.h"

//============================
//マクロ定義
//============================

//============================
//構造体定義
//============================
struct PLAYER
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//大きさ
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//テクスチャ番号
	int HP;
	int sound;
	int invCounter;

	float rotation;	//回転角度

	bool use;	//構造体使用中フラグ
	bool animate;
	bool invincible;
};

//============================
//プロトタイプ宣言
//============================
HRESULT InitPlayer();	//初期化
void UnInitPlayer();	//終了処理
void DrawPlayer();	//描写処理
void UpdatePlayer();	//更新処理

PLAYER* GetPlayer();	//構造体の先頭のポインタを返す
#pragma once

#include "main.h"
#include "renderer.h"

//============================
//マクロ定義
//============================
#define EXPLOSION_MAX 200

//============================
//構造体定義
//============================
struct EXPLOSION
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//大きさ
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;
	int flip;
	int TextNo;

	float rotation;	//回転角度

	bool use;	//構造体使用中フラグ
};

//============================
//プロトタイプ宣言
//============================
HRESULT InitExplosion();	//初期化
void UnInitExplosion();	//終了処理
void DrawExplosion();	//描写処理
void UpdateExplosion();	//更新処理

EXPLOSION* GetExplosion();	//構造体の先頭のポインタを返す
void SetExplosion(D3DXVECTOR2 Position, D3DXVECTOR2 Size, D3DXCOLOR Color, float Volume);
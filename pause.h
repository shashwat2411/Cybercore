#pragma once

#include "main.h"
#include "renderer.h"

//============================
//マクロ定義
//============================


//============================
//構造体定義
//============================
struct PAUSE
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//大きさ
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//テクスチャ番号

	float rotation;	//回転角度

	bool use;	//構造体使用中フラグ
};

//============================
//プロトタイプ宣言
//============================
HRESULT InitPause();	//初期化
void UnInitPause();	//終了処理
void DrawPause();	//描写処理
void UpdatePause();	//更新処理

PAUSE* GetPause();
#pragma once

#include "main.h"
#include "renderer.h"

//============================
//マクロ定義
//============================


//============================
//構造体定義
//============================
struct BG
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//大きさ
	D3DXVECTOR2 Offset;	//テクスチャ初期座標
	D3DXVECTOR2 Coordinate;	//テクスチャ増加値

	D3DXCOLOR color;	//色

	int imageNum;	//テクスチャのイメージの位置
	int flip;	//フリップ表示
	int TextNo;	//テクスチャ番号

	float rotation;	//回転角度

	bool use;	//構造体使用中フラグ
};

//============================
//プロトタイプ宣言
//============================
HRESULT InitBG();	//初期化
void UnInitBG();	//終了処理
void DrawBG();	//描写処理
void UpdateBG();	//更新処理

BG* GetBG();	//構造体の先頭のポインタを返す
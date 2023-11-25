#pragma once

#include "main.h"
#include "renderer.h"

//============================
//マクロ定義
//============================
#define BULLET_MAX 200

//============================
//構造体定義
//============================
struct BULLET
{
	D3DXVECTOR2 Position;	//表示座標
	D3DXVECTOR2 Size;	//大きさ
	D3DXVECTOR2 Offset;	//テクスチャ初期座標
	D3DXVECTOR2 Coordinate;	//テクスチャ増加値
	D3DXVECTOR2 Speed;	//速度

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
HRESULT InitBullet();	//初期化
void UnInitBullet();	//終了処理
void DrawBullet();	//描写処理
void UpdateBullet();	//更新処理

BULLET* GetBullet();	//構造体の先頭のポインタを返す
void SetBullet();	//セット情報を渡す

BULLET* GetEnemyBullet();	//構造体の先頭のポインタを返す
void SetEnemyBullet(D3DXVECTOR2 Position, D3DXVECTOR2 Head);	//セット情報を渡す
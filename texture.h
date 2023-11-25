#pragma once
#include "main.h"
#include "renderer.h"

//関数四天王
void InitTexture();
void UnInitTexture();	//ロード済みのテクスチャを全て解放
//void SetTexture(float, float, int, int, float, D3DXCOLOR);	//三角形用頂点格納処理

void SetTexture(int Texture);
int LoadTexture(char* filename);	//In：テクスチャファイル名の先頭ポインタ、Out：ロードしたテクスチャハンドル
ID3D11ShaderResourceView** GetTexture(int index);	//指定のテクスチャ情報を取得、In：使用したいテクスチャハンドル、Out：テクスチャ情報のポインタの入ったポインタ変数のポインタ
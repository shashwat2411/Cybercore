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
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�傫��
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//�e�N�X�`���ԍ�
	int type;

	float rotation;	//��]�p�x

	bool use;	//�\���̎g�p���t���O
};

HRESULT InitFade();
void UnInitFade();
void UpdateFade();
void DrawFade();

void SetFade(TYPE type);
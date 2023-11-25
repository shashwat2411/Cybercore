#pragma once

#include "main.h"
#include "renderer.h"

//============================
//�}�N����`
//============================
#define ENEMY_NUMBER_MAX 100

#define ENEMY_HORIZONTAL 8
#define ENEMY_VERTICAL 3

#define ENEMY_MAX 10

#define DISTANCE_X 100
#define DISTANCE_Y 80

#define SECONDS 100.0f
//============================
//�\���̒�`
//============================
struct ENEMY
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�傫��
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;
	D3DXVECTOR2 Speed;

	D3DXCOLOR color;

	int imageNum;	
	int flip;
	int TextNo;	//�e�N�X�`���ԍ�
	int HP;

	float rotation;	//��]�p�x
	float frameWait;

	bool use;	//�\���̎g�p���t���O
	bool blink;
};

//============================
//�v���g�^�C�v�錾
//============================
HRESULT InitEnemy();
void UnInitEnemy();
void DrawEnemy();
void UpdateEnemy();

ENEMY* GetEnemy();

void SetEnemy(ENEMY* Enemy, D3DXVECTOR2 Position);
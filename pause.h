#pragma once

#include "main.h"
#include "renderer.h"

//============================
//�}�N����`
//============================


//============================
//�\���̒�`
//============================
struct PAUSE
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�傫��
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//�e�N�X�`���ԍ�

	float rotation;	//��]�p�x

	bool use;	//�\���̎g�p���t���O
};

//============================
//�v���g�^�C�v�錾
//============================
HRESULT InitPause();	//������
void UnInitPause();	//�I������
void DrawPause();	//�`�ʏ���
void UpdatePause();	//�X�V����

PAUSE* GetPause();
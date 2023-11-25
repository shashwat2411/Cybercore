#pragma once

#include "main.h"
#include "renderer.h"

//============================
//�}�N����`
//============================
#define DIGITS 3

//============================
//�\���̒�`
//============================
struct SCORE
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�傫��
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//�e�N�X�`���ԍ�
	int Score;

	float rotation;	//��]�p�x

	bool use;	//�\���̎g�p���t���O
};

//============================
//�v���g�^�C�v�錾
//============================
HRESULT InitScore();	//������
void UnInitScore();	//�I������
void DrawScore();	//�`�ʏ���
void UpdateScore();	//�X�V����

SCORE* GetScore();	//�\���̂̐擪�̃|�C���^��Ԃ�
int* GetRealScore();
#pragma once

#include "main.h"
#include "renderer.h"

//============================
//�}�N����`
//============================
#define LIFEPOINTS 5

//============================
//�\���̒�`
//============================
struct LIFE
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�傫��
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//�e�N�X�`���ԍ�
	int Life;

	float rotation;	//��]�p�x

	bool use;	//�\���̎g�p���t���O
};

//============================
//�v���g�^�C�v�錾
//============================
HRESULT InitLife();	//������
void UnInitLife();	//�I������
void DrawLife();	//�`�ʏ���
void UpdateLife();	//�X�V����

LIFE* GetLife();	//�\���̂̐擪�̃|�C���^��Ԃ�
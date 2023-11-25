#pragma once

#include "main.h"
#include "renderer.h"

//============================
//�}�N����`
//============================

//============================
//�\���̒�`
//============================
struct PLAYER
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�傫��
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;	//
	int flip;
	int TextNo;	//�e�N�X�`���ԍ�
	int HP;
	int sound;
	int invCounter;

	float rotation;	//��]�p�x

	bool use;	//�\���̎g�p���t���O
	bool animate;
	bool invincible;
};

//============================
//�v���g�^�C�v�錾
//============================
HRESULT InitPlayer();	//������
void UnInitPlayer();	//�I������
void DrawPlayer();	//�`�ʏ���
void UpdatePlayer();	//�X�V����

PLAYER* GetPlayer();	//�\���̂̐擪�̃|�C���^��Ԃ�
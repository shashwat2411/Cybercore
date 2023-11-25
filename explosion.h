#pragma once

#include "main.h"
#include "renderer.h"

//============================
//�}�N����`
//============================
#define EXPLOSION_MAX 200

//============================
//�\���̒�`
//============================
struct EXPLOSION
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�傫��
	D3DXVECTOR2 Offset;
	D3DXVECTOR2 Coordinate;

	D3DXCOLOR color;

	int imageNum;
	int flip;
	int TextNo;

	float rotation;	//��]�p�x

	bool use;	//�\���̎g�p���t���O
};

//============================
//�v���g�^�C�v�錾
//============================
HRESULT InitExplosion();	//������
void UnInitExplosion();	//�I������
void DrawExplosion();	//�`�ʏ���
void UpdateExplosion();	//�X�V����

EXPLOSION* GetExplosion();	//�\���̂̐擪�̃|�C���^��Ԃ�
void SetExplosion(D3DXVECTOR2 Position, D3DXVECTOR2 Size, D3DXCOLOR Color, float Volume);
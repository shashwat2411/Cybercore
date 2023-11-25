#pragma once

#include "main.h"
#include "renderer.h"

//============================
//�}�N����`
//============================


//============================
//�\���̒�`
//============================
struct BG
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�傫��
	D3DXVECTOR2 Offset;	//�e�N�X�`���������W
	D3DXVECTOR2 Coordinate;	//�e�N�X�`�������l

	D3DXCOLOR color;	//�F

	int imageNum;	//�e�N�X�`���̃C���[�W�̈ʒu
	int flip;	//�t���b�v�\��
	int TextNo;	//�e�N�X�`���ԍ�

	float rotation;	//��]�p�x

	bool use;	//�\���̎g�p���t���O
};

//============================
//�v���g�^�C�v�錾
//============================
HRESULT InitBG();	//������
void UnInitBG();	//�I������
void DrawBG();	//�`�ʏ���
void UpdateBG();	//�X�V����

BG* GetBG();	//�\���̂̐擪�̃|�C���^��Ԃ�
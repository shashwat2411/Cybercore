#pragma once

#include "main.h"
#include "renderer.h"

//============================
//�}�N����`
//============================
#define BULLET_MAX 200

//============================
//�\���̒�`
//============================
struct BULLET
{
	D3DXVECTOR2 Position;	//�\�����W
	D3DXVECTOR2 Size;	//�傫��
	D3DXVECTOR2 Offset;	//�e�N�X�`���������W
	D3DXVECTOR2 Coordinate;	//�e�N�X�`�������l
	D3DXVECTOR2 Speed;	//���x

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
HRESULT InitBullet();	//������
void UnInitBullet();	//�I������
void DrawBullet();	//�`�ʏ���
void UpdateBullet();	//�X�V����

BULLET* GetBullet();	//�\���̂̐擪�̃|�C���^��Ԃ�
void SetBullet();	//�Z�b�g����n��

BULLET* GetEnemyBullet();	//�\���̂̐擪�̃|�C���^��Ԃ�
void SetEnemyBullet(D3DXVECTOR2 Position, D3DXVECTOR2 Head);	//�Z�b�g����n��
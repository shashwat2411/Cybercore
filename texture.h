#pragma once
#include "main.h"
#include "renderer.h"

//�֐��l�V��
void InitTexture();
void UnInitTexture();	//���[�h�ς݂̃e�N�X�`����S�ĉ��
//void SetTexture(float, float, int, int, float, D3DXCOLOR);	//�O�p�`�p���_�i�[����

void SetTexture(int Texture);
int LoadTexture(char* filename);	//In�F�e�N�X�`���t�@�C�����̐擪�|�C���^�AOut�F���[�h�����e�N�X�`���n���h��
ID3D11ShaderResourceView** GetTexture(int index);	//�w��̃e�N�X�`�������擾�AIn�F�g�p�������e�N�X�`���n���h���AOut�F�e�N�X�`�����̃|�C���^�̓������|�C���^�ϐ��̃|�C���^
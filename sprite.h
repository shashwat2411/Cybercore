//=============================
//�X�v���C�g�`�揈��
//=============================

#pragma once
#include "main.h"
#include "renderer.h"

//�֐��l�V��
void InitTriangle();
void UnInitTriangle();
void DrawTriangle();
void UpdateTriangle();

void DrawSpriteColorRotate(float posX, float posY, int size_w, int size_h, float kakudo, D3DXCOLOR color, int* ImageNum, float* offsetX, float* offsetY, float yoko, float tate, float yoko_num, int flip, bool animate);
void SpriteSheet(float * X, float * Y, int * imageNum, int yoko_num, float yoko, float tate, int count, int frame);

float generateRandom(float min, float max);
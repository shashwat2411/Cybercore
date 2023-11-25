#include "bg.h"
#include "sprite.h"
#include "texture.h"
#include "input.h"

//============================
//�}�N����`
//============================

//============================
//�v���g�^�C�v�錾
//============================

//============================
//�O���[�o���ϐ�
//============================
static BG g_Bg;

char TextNoBG[] = "data/texture/background.jpg";
//============================
//������
//============================
HRESULT InitBG()
{
	//�v���[���[�\���̂̏�����
	{
		g_Bg.TextNo = LoadTexture(TextNoBG);

		g_Bg.Position.x = SCREEN_WIDTH / 2;
		g_Bg.Position.y = SCREEN_HEIGHT / 2;

		g_Bg.Size.x = SCREEN_WIDTH;
		g_Bg.Size.y = SCREEN_HEIGHT;

		g_Bg.use = true;

		g_Bg.rotation = 0.0f;
		g_Bg.imageNum = 0;

		g_Bg.Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Bg.Coordinate = D3DXVECTOR2(1.0f, 1.0f);

		g_Bg.color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_Bg.flip = 0;
	}

	return S_OK;
}

//============================
//�I������
//============================
void UnInitBG()
{

}

//============================
//�`�揈��
//============================
void DrawBG()
{
	DrawTriangle();
	SetWorldViewProjection2D();

	SetTexture(g_Bg.TextNo);
	DrawSpriteColorRotate
	(
		g_Bg.Position.x, 
		g_Bg.Position.y, 
		g_Bg.Size.x, 
		g_Bg.Size.y, 
		g_Bg.rotation, 
		g_Bg.color, 
		&g_Bg.imageNum, 
		&(g_Bg.Offset.x), 
		&(g_Bg.Offset.y), 
		g_Bg.Coordinate.x, 
		g_Bg.Coordinate.y, 
		1, 
		g_Bg.flip, 
		false
	);
	
	GetDeviceContext()->Draw(4, 0);
}

//============================
//�X�V����
//============================
void UpdateBG()
{
	g_Bg.Offset.y -= 0.002f;
}

//============================
//�\���̂̐퓬�|�C���^��Ԃ�
//============================
BG * GetBG()
{
	return &g_Bg;
}

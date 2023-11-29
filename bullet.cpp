#include "bullet.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "sound.h"
#include "player.h"



//============================
//�}�N����`
//============================
#define BULLET_SIZE_X 50.0f
#define BULLET_SIZE_Y 50.0f

#define BULLET_SPEED 8.0f
#define ENEMY_BULLET_SPEED 2.5f
//============================
//�v���g�^�C�v�錾
//============================

//============================
//�O���[�o���ϐ�
//============================
static BULLET g_Bullet[BULLET_MAX];
static BULLET g_EnemyBullet[BULLET_MAX];
static PLAYER* Player;

D3DXVECTOR2 HeadPosition;

int BulletSoundNo = 0; //�T�E���h��\���C���f�b�N�X�ԍ�

char TextNo1[] = "data/texture/bullet.png";
char TextNo2[] = "data/texture/enemybullet.png";
//============================
//������
//============================
HRESULT InitBullet()
{
	g_Bullet[0].TextNo = LoadTexture(TextNo1);
	g_EnemyBullet[0].TextNo = LoadTexture(TextNo2);

	//�v���[���[�̒e
	for (int i = 0; i < BULLET_MAX; i++)
	{		
		g_Bullet[i].Position.x = SCREEN_WIDTH / 2;
		g_Bullet[i].Position.y = SCREEN_HEIGHT / 2;
				
		g_Bullet[i].Size.x = 20.0f;
		g_Bullet[i].Size.y = 20.0f;
				
		g_Bullet[i].use = false;
				
		g_Bullet[i].rotation = 0.0f;
				
		g_Bullet[i].Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_Bullet[i].Coordinate = D3DXVECTOR2(1.0f, 1.0f);
				
		g_Bullet[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				
		g_Bullet[i].flip = 0;
	}

	//�G�̒e
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_EnemyBullet[i].Position.x = SCREEN_WIDTH / 2;
		g_EnemyBullet[i].Position.y = SCREEN_HEIGHT / 2;

		g_EnemyBullet[i].Size.x = BULLET_SIZE_X;
		g_EnemyBullet[i].Size.y = BULLET_SIZE_Y;

		g_EnemyBullet[i].use = false;

		g_EnemyBullet[i].rotation = 0.0f;

		g_EnemyBullet[i].Offset = D3DXVECTOR2(0.0f, 0.0f);
		g_EnemyBullet[i].Coordinate = D3DXVECTOR2(1.0f, 1.0f);

		g_EnemyBullet[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_EnemyBullet[i].flip = 0;
	}

	//�T�E���h�f�[�^�̃��[�h
	char filename[] = "data\\SE\\shot000.wav";
	BulletSoundNo = LoadSound(filename);
	SetVolume(BulletSoundNo, 0.5);

	return S_OK;
}

//============================
//�I������
//============================
void UnInitBullet()
{
	
}

//============================
//�`�揈��
//============================
void DrawBullet()
{
	DrawTriangle();
	SetWorldViewProjection2D();

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == true)
		{
			SetTexture(g_Bullet[0].TextNo);
			SetBlendState(BLEND_MODE_ADD);
			DrawSpriteColorRotate(
				g_Bullet[i].Position.x,
				g_Bullet[i].Position.y,
				g_Bullet[i].Size.x,
				g_Bullet[i].Size.y,
				g_Bullet[i].rotation,
				g_Bullet[i].color,
				&g_Bullet[i].imageNum,
				&(g_Bullet[i].Offset.x),
				&(g_Bullet[i].Offset.y),
				g_Bullet[i].Coordinate.x,
				g_Bullet[i].Coordinate.y,
				1,
				g_Bullet[i].flip,
				false
			);

			GetDeviceContext()->Draw(4, 0);
			SetBlendState(BLEND_MODE_ALPHABLEND);
		}

		if (g_EnemyBullet[i].use == true)
		{
			SetTexture(g_EnemyBullet[0].TextNo);
			DrawSpriteColorRotate(
				g_EnemyBullet[i].Position.x,
				g_EnemyBullet[i].Position.y,
				g_EnemyBullet[i].Size.x,
				g_EnemyBullet[i].Size.y,
				g_EnemyBullet[i].rotation,
				g_EnemyBullet[i].color,
				&g_EnemyBullet[i].imageNum,
				&(g_EnemyBullet[i].Offset.x),
				&(g_EnemyBullet[i].Offset.y),
				g_EnemyBullet[i].Coordinate.x,
				g_EnemyBullet[i].Coordinate.y,
				1,
				g_EnemyBullet[i].flip,
				false
			);

			g_EnemyBullet[i].rotation += 10.0f;
			if (g_EnemyBullet[i].rotation >= 360.0f) 
			{ 
				g_EnemyBullet[i].rotation -= g_EnemyBullet[i].rotation;
			}

			GetDeviceContext()->Draw(4, 0);
		}
	}
}

//============================
//�X�V����
//============================
void UpdateBullet()
{
	Player = GetPlayer();

	for (int i = 0; i < BULLET_MAX; i++)
	{
		float rad = D3DXToRadian(g_Bullet[i].rotation);

		g_Bullet[i].Position.x += sinf(rad) * BULLET_SPEED;
		g_Bullet[i].Position.y += cosf(rad) * -BULLET_SPEED;

		if (g_Bullet[i].Position.x > SCREEN_WIDTH || g_Bullet[i].Position.x < 0 || g_Bullet[i].Position.y > SCREEN_HEIGHT || g_Bullet[i].Position.y < 0)
		{
			g_Bullet[i].use = false;
		}
	}

	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_EnemyBullet[i].Position += g_EnemyBullet[i].Speed;

		if (g_EnemyBullet[i].Position.x > SCREEN_WIDTH || g_EnemyBullet[i].Position.x < 0 || g_EnemyBullet[i].Position.y > SCREEN_HEIGHT || g_EnemyBullet[i].Position.y < 0)
		{
			g_EnemyBullet[i].use = false;
		}
	}
}

//============================
//�\���̂̐퓬�|�C���^��Ԃ�
//============================
BULLET* GetBullet()
{
	return &g_Bullet[0];
}

BULLET* GetEnemyBullet()
{
	return &g_EnemyBullet[0];
}

void SetBullet()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].use == false)
		{
			g_Bullet[i].Position.x = Player->Position.x;
			g_Bullet[i].Position.y = Player->Position.y;//	 -Player->Size.y / 2;
			g_Bullet[i].rotation = Player->rotation;
			g_Bullet[i].use = true;
			SetVolume(BulletSoundNo,0.06f);
			PlaySoundInGame(BulletSoundNo, 0); //�e�����˂��ꂽ�����Đ�
			return;
		}
	}
}

void SetEnemyBullet(D3DXVECTOR2 Position, D3DXVECTOR2 Head)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_EnemyBullet[i].use == false)
		{
			g_EnemyBullet[i].Position = Position;
			g_EnemyBullet[i].use = true;


			HeadPosition = Head;
			D3DXVECTOR2 temp;
			temp = HeadPosition - g_EnemyBullet[i].Position;
			D3DXVec2Normalize(&temp, &temp);
			temp *= ENEMY_BULLET_SPEED;


			g_EnemyBullet[i].Speed = temp;
			return;
		}
	}
}

//====================================
//当たり判定処理
//====================================

#include "main.h"
#include "collision.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "sound.h"

//====================================
//マクロ定義
//====================================
//#define ROOT
#define EXTRA 5.0f

#define PLAYER_BOX_X 10.0f
#define PLAYER_BOX_Y 5.0f
//====================================
//グローバル変数
//====================================
PLAYER* Player;
ENEMY* Enemy;
BULLET* Bullet;
BULLET* EnemyBullet;
EXPLOSION* Explosion;
SCORE* Score;
int* RealScore;

int comeBack = 0;
bool back = false;


//====================================
//プロトタイプ宣言
//====================================

//__________________________________________________________________________
//in	 四角形１中心座標、四角形２中心座標、四角形１サイズ、四角形２サイズ |
//out	 true : 衝突している、false : 衝突していない                        |
bool CollisionBB(D3DXVECTOR2 Box1, D3DXVECTOR2 Box2, D3DXVECTOR2 Size1, D3DXVECTOR2 Size2);	//BB → Bounding Box
//____________________________________________________________________
//in	 円形１中心座標、円形２中心座標、円形１サイズ、円形２サイズ   |
//out	 true : 衝突している、false : 衝突していない                  |
bool CollisionBC(D3DXVECTOR2 Circle1, D3DXVECTOR2 Circle2, float Size1, float Size2);	//BC → Bounding Circle


//====================================
//当たり判定
//====================================
void UpdateCollision()
{
	Player = GetPlayer();
	Enemy = GetEnemy();
	Bullet = GetBullet();
	EnemyBullet = GetEnemyBullet();
	//Explosion = GetExplosion();
	Score = GetScore();
	RealScore = GetRealScore();

	//Player & Enemy
	if (Player->use == true)
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (Enemy[i].use != true) continue;

			bool hit = CollisionBB(Player->Position, Enemy[i].Position, Player->Size - D3DXVECTOR2(PLAYER_BOX_X, PLAYER_BOX_Y), Enemy[i].Size);
			if (hit == true && Player->invincible == false)
			{
				Player->HP--;
				Player->invincible = true;
				Player->color.g = 0.0f;
				Player->color.b = 0.0f;

				SetVolume(Player->sound, 0.2f);
				PlaySoundInGame(Player->sound, 0);

				back = true;
			}
			else
			{
				if (comeBack > 20)
				{
					Player->color.g = 1.0f;
					Player->color.b = 1.0f;

					comeBack = 0;
					back = false;
				}
			}
			if (back == true)
			{
				comeBack++;
			}
		}

		//Enemy & PlayerBullet
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if ((Enemy + i)->use != true) continue;

			for (int j = 0; j < BULLET_MAX; j++)
			{
				if ((Bullet + j)->use != true) continue;

				Enemy[i].color.g = 1.0f;
				Enemy[i].color.b = 1.0f;

				bool hit = CollisionBC(Enemy[i].Position, (Bullet + j)->Position, (Enemy + i)->Size.x / 2, (Bullet + j)->Size.x / 2);
				if (hit == true)
				{
					Enemy[i].HP += -1;
					Enemy[i].color.g = 0.0f;
					Enemy[i].color.b = 0.0f;
					Enemy[i].blink = true;

					*RealScore += 1;

					Bullet[j].use = false;
					SetExplosion(Bullet[j].Position, D3DXVECTOR2(50.0f, 50.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.05f);
				}
			}
		}

		//Player & EnemyBullet
		if (Player->use == true)
		{
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if ((EnemyBullet + i)->use != true) continue;

				bool hit = CollisionBB(Player->Position, (EnemyBullet + i)->Position, Player->Size - D3DXVECTOR2(PLAYER_BOX_X, PLAYER_BOX_Y), EnemyBullet[i].Size);
				if (hit == true && Player->invincible == false)
				{
					Player->HP--;
					Player->invincible = true;
					Player->color.g = 0.0f;
					Player->color.b = 0.0f;

					back = true;

					EnemyBullet[i].use = false;
					SetExplosion(EnemyBullet[i].Position, D3DXVECTOR2(30.0f, 30.0f), D3DXCOLOR(0.53f, 0.27f, 0.05f, 1.0f), 0.06f);
				}
				else
				{
					if (comeBack > 20)
					{
						Player->color.g = 1.0f;
						Player->color.b = 1.0f;

						comeBack = 0;
						back = false;
					}
				}
			}
		}

		//PlayerBullet & EnemyBullet
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (Bullet[i].use != true) continue;

			for (int j = 0; j < BULLET_MAX; j++)
			{
				if (EnemyBullet[j].use != true) continue;

				bool hit = CollisionBC(Bullet[i].Position, EnemyBullet[j].Position, Bullet[i].Size.x / 2, EnemyBullet[j].Size.x / 2);
				if (hit == true)
				{
					Bullet[i].use = false;
					EnemyBullet[j].use = false;

					SetExplosion((Bullet[i].Position + EnemyBullet[j].Position) / 2, D3DXVECTOR2(30.0f, 30.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 0.03f);
				}
			}
		}
		
	}

}


bool CollisionBB(D3DXVECTOR2 Pos1, D3DXVECTOR2 Pos2, D3DXVECTOR2 Size1, D3DXVECTOR2 Size2)
{
	D3DXVECTOR2 Min1, Max1;	//四角形１
	D3DXVECTOR2 Min2, Max2;	//四角形２

	//四角形１
	Min1.x = Pos1.x - (Size1.x / 2 - EXTRA);	//四角形１左上
	Min1.y = Pos1.y - (Size1.y / 2 - EXTRA);

	Max1.x = Pos1.x + (Size1.x / 2 - EXTRA);	//四角形１右下
	Max1.y = Pos1.y + (Size1.y / 2 - EXTRA);


	//四角形２
	Min2.x = Pos2.x - (Size2.x / 2 - EXTRA);	//四角形２左上
	Min2.y = Pos2.y - (Size2.y / 2 - EXTRA);
	   					  
	Max2.x = Pos2.x + (Size2.x / 2 - EXTRA);	//四角形２右下
	Max2.y = Pos2.y + (Size2.y / 2 - EXTRA);
	   					  

	//衝突判定
	if (Max1.x < Min2.x)	return false;	//条件１	衝突しない
	else if (Max1.y < Min2.y)	return false;//条件２	衝突しない
	else if (Max2.x < Min1.x)	return false;//条件３	衝突しない
	else if (Max2.y < Min1.y) return false;//条件４	衝突しない

	return true;
}

bool CollisionBC(D3DXVECTOR2 Pos1, D3DXVECTOR2 Pos2, float Size1, float Size2)
{
	//中心同士のベクトルを作る
	//(Pos1-Pos2) → Pos2に向かうベクトル
	D3DXVECTOR2 vDistance = Pos1 - Pos2;

	//vDistanceの長さを計算
#ifdef ROOT
	float Length = D3DXVec2LengthSq(&vDistance);	//√する
	float Size = Size1 + Size2;	//√する
#else
	float Length = D3DXVec2LengthSq(&vDistance);	//√しない
	float Size = (Size1 + Size2) * (Size1 + Size2);	//√しない

#endif
	
	//中心同士の距離と半径の総和を比べる
	if (Length <= Size)
		return true;	//衝突している

	return false;	//衝突していない
}

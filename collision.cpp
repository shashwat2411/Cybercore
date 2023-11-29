//====================================
//“–‚½‚è”»’èˆ—
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
//ƒ}ƒNƒ’è‹`
//====================================
//#define ROOT
#define EXTRA 5.0f

#define PLAYER_BOX_X 10.0f
#define PLAYER_BOX_Y 5.0f
//====================================
//ƒOƒ[ƒoƒ‹•Ï”
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
//ƒvƒƒgƒ^ƒCƒvéŒ¾
//====================================

//__________________________________________________________________________
//in	 ŽlŠpŒ`‚P’†SÀ•WAŽlŠpŒ`‚Q’†SÀ•WAŽlŠpŒ`‚PƒTƒCƒYAŽlŠpŒ`‚QƒTƒCƒY |
//out	 true : Õ“Ë‚µ‚Ä‚¢‚éAfalse : Õ“Ë‚µ‚Ä‚¢‚È‚¢                        |
bool CollisionBB(D3DXVECTOR2 Box1, D3DXVECTOR2 Box2, D3DXVECTOR2 Size1, D3DXVECTOR2 Size2);	//BB ¨ Bounding Box
//____________________________________________________________________
//in	 ‰~Œ`‚P’†SÀ•WA‰~Œ`‚Q’†SÀ•WA‰~Œ`‚PƒTƒCƒYA‰~Œ`‚QƒTƒCƒY   |
//out	 true : Õ“Ë‚µ‚Ä‚¢‚éAfalse : Õ“Ë‚µ‚Ä‚¢‚È‚¢                  |
bool CollisionBC(D3DXVECTOR2 Circle1, D3DXVECTOR2 Circle2, float Size1, float Size2);	//BC ¨ Bounding Circle


//====================================
//“–‚½‚è”»’è
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
	D3DXVECTOR2 Min1, Max1;	//ŽlŠpŒ`‚P
	D3DXVECTOR2 Min2, Max2;	//ŽlŠpŒ`‚Q

	//ŽlŠpŒ`‚P
	Min1.x = Pos1.x - (Size1.x / 2 - EXTRA);	//ŽlŠpŒ`‚P¶ã
	Min1.y = Pos1.y - (Size1.y / 2 - EXTRA);

	Max1.x = Pos1.x + (Size1.x / 2 - EXTRA);	//ŽlŠpŒ`‚P‰E‰º
	Max1.y = Pos1.y + (Size1.y / 2 - EXTRA);


	//ŽlŠpŒ`‚Q
	Min2.x = Pos2.x - (Size2.x / 2 - EXTRA);	//ŽlŠpŒ`‚Q¶ã
	Min2.y = Pos2.y - (Size2.y / 2 - EXTRA);
	   					  
	Max2.x = Pos2.x + (Size2.x / 2 - EXTRA);	//ŽlŠpŒ`‚Q‰E‰º
	Max2.y = Pos2.y + (Size2.y / 2 - EXTRA);
	   					  

	//Õ“Ë”»’è
	if (Max1.x < Min2.x)	return false;	//ðŒ‚P	Õ“Ë‚µ‚È‚¢
	else if (Max1.y < Min2.y)	return false;//ðŒ‚Q	Õ“Ë‚µ‚È‚¢
	else if (Max2.x < Min1.x)	return false;//ðŒ‚R	Õ“Ë‚µ‚È‚¢
	else if (Max2.y < Min1.y) return false;//ðŒ‚S	Õ“Ë‚µ‚È‚¢

	return true;
}

bool CollisionBC(D3DXVECTOR2 Pos1, D3DXVECTOR2 Pos2, float Size1, float Size2)
{
	//’†S“¯Žm‚ÌƒxƒNƒgƒ‹‚ðì‚é
	//(Pos1-Pos2) ¨ Pos2‚ÉŒü‚©‚¤ƒxƒNƒgƒ‹
	D3DXVECTOR2 vDistance = Pos1 - Pos2;

	//vDistance‚Ì’·‚³‚ðŒvŽZ
#ifdef ROOT
	float Length = D3DXVec2LengthSq(&vDistance);	//ã‚·‚é
	float Size = Size1 + Size2;	//ã‚·‚é
#else
	float Length = D3DXVec2LengthSq(&vDistance);	//ã‚µ‚È‚¢
	float Size = (Size1 + Size2) * (Size1 + Size2);	//ã‚µ‚È‚¢

#endif
	
	//’†S“¯Žm‚Ì‹——£‚Æ”¼Œa‚Ì‘˜a‚ð”ä‚×‚é
	if (Length <= Size)
		return true;	//Õ“Ë‚µ‚Ä‚¢‚é

	return false;	//Õ“Ë‚µ‚Ä‚¢‚È‚¢
}

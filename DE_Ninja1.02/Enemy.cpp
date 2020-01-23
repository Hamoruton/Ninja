#include "DxLib.h"
#include "Task2DACT.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Effect.h"
#include "Scene.h"

//========================================================================
//コンストラクタ
//========================================================================
CSmallEnemy::CSmallEnemy(float x, float y)
	:CEnemy(x, y, -50.0f, -50.0f, 50.0f, 50.0f, 1, 100), Count(0)
{
	GHEnemyScroll = LoadGraph("Sprites\\Enemy\\Scroll.png");
}


//========================================================================
//移動
//========================================================================
bool CSmallEnemy::Move() 
{
	if (Game->Gauge == 0) {
		return false;
	}

	X -= 0.5f;

	if (Time % 200 == 0) {
		for (int i = 0; i <= 180; i += 60) {
			new CDirBullet(X, Y, 1.0f*i + GetRand(10), 0.2f, 0.1f);
		}
	}
	Time++;

	if (Vit <= 0) {
		new CEnemyCrash(X - 50, Y - 50);
		return false;
	}

	if (Game->DefeatCount >= MAX_DEFEAT) {
		return false;
	}

	return Y < SCREEN_HEIGHT + 8;
}


//========================================================================
//描画
//========================================================================
void CSmallEnemy::Draw() 
{
	DrawRotaGraph3(X - ENEMY_SCROLL_CHIP_SIZE_X * ENEMY_SCROLL_REDUCTION / 2, Y - ENEMY_SCROLL_CHIP_SIZE_Y * ENEMY_SCROLL_REDUCTION / 2,
		ENEMY_SCROLL_CHIP_SIZE_X / 2, ENEMY_SCROLL_CHIP_SIZE_Y / 2, ENEMY_SCROLL_REDUCTION, ENEMY_SCROLL_REDUCTION, Time / 10, GHEnemyScroll, TRUE, FALSE);
}

//========================================================================
//コンストラクタ
//========================================================================
CSmallEnemy2::CSmallEnemy2(float x, float y)
	:CEnemy(x, y, -50.0f, -50.0f, 50.0f, 50.0f, 1, 100), Count(0)
{
	GHEnemyScroll = LoadGraph("Sprites\\Enemy\\Scroll.png");
}


//========================================================================
//移動
//========================================================================
bool CSmallEnemy2::Move()
{
	if (Game->Gauge == 0) {
		return false;
	}
	
	X += 0.8f;

	if (Time % 200 == 0) {
		for (int i = 0; i <= 180; i += 60) {
			new CDirBullet(X, Y, 1.0f*i + GetRand(10), 0.2f, 0.1f);
		}
	}
	Time++;

	if (Vit <= 0) {
		new CEnemyCrash(X - 50, Y - 50);
		return false;
	}

	if (Game->DefeatCount >= MAX_DEFEAT) {
		return false;
	}

	return Y < SCREEN_HEIGHT + 8;
}


//========================================================================
//描画
//========================================================================
void CSmallEnemy2::Draw()
{
	DrawRotaGraph3(X - ENEMY_SCROLL_CHIP_SIZE_X * ENEMY_SCROLL_REDUCTION / 2, Y - ENEMY_SCROLL_CHIP_SIZE_Y * ENEMY_SCROLL_REDUCTION / 2,
		ENEMY_SCROLL_CHIP_SIZE_X / 2, ENEMY_SCROLL_CHIP_SIZE_Y / 2, ENEMY_SCROLL_REDUCTION, ENEMY_SCROLL_REDUCTION, Time / 8, GHEnemyScroll, TRUE, FALSE);
}


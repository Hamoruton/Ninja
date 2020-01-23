#include "DxLib.h"
#include "Task2DACT.h"
#include "Player.h"
#include "Enemy.h"
#include "Effect.h"
#include "Scene.h"
#include "UI.h"

//========================================================================
//コンストラクタ
//========================================================================
CPlayerCrash::CPlayerCrash(float x, float y)
	:CEffect(x, y, 0, 0, 0, 0), Time(0), Count(0)
{
	SEPlayerCrash = LoadSoundMem(CRASH_PLAYER_SE);
	PlaySoundMem(SEPlayerCrash, DX_PLAYTYPE_BACK);

	LoadDivGraph(CRASH_PLAYER_CHIP, CRASH_PLAYER_PATTERN, CRASH_PLAYER_PATTERN, 1, 
		CRASH_PLAYER_SIZE_X, CRASH_PLAYER_SIZE_Y, GHPlayerCrash);
}

//========================================================================
//移動
//========================================================================
bool CPlayerCrash::Move() 
{
	if (Game->Gauge == 0) {
		return false;
	}
	if (Game->DefeatCount == MAX_DEFEAT) {
			return false;
	}

	Time++;
	Count++;

	if (Time >= 85) {
		new CRevivalPlayer(X, Y);

		//エフェクトを消す
		return false;
	}
	return true;
}

//========================================================================
//描画
//========================================================================
void CPlayerCrash::Draw() 
{
	DrawGraphF(X - (CRASH_PLAYER_SIZE_X / 2), Y - (CRASH_PLAYER_SIZE_Y / 2), GHPlayerCrash[(Count / CRASH_PLAYER_ANIM_SPEED) % CRASH_PLAYER_PATTERN], TRUE);
}

//========================================================================
//コンストラクタ
//========================================================================
CPlayerCrash2::CPlayerCrash2(float x, float y)
	:CEffect(x, y, 0, 0, 0, 0), Time(0), Count(0)
{
	SEPlayerCrash2 = LoadSoundMem(CRASH2_PLAYER_SE);
	PlaySoundMem(SEPlayerCrash2, DX_PLAYTYPE_BACK);

	LoadDivGraph(CRASH2_PLAYER_CHIP, CRASH2_PLAYER_PATTERN, 5, 2,
		CRASH_PLAYER_SIZE_X, CRASH_PLAYER_SIZE_Y, GHPlayerCrash2);
}

//========================================================================
//移動
//========================================================================
bool CPlayerCrash2::Move()
{
	Time++;
	Count++;

	if (Time >= 85) {
		new CRevivalPlayer(X, Y);

		//エフェクトを消す
		return false;
	}
	return true;
}

//========================================================================
//描画
//========================================================================
void CPlayerCrash2::Draw()
{
	DrawGraphF(X - (CRASH2_PLAYER_SIZE_X / 2), Y - (CRASH2_PLAYER_SIZE_Y / 2), GHPlayerCrash2[(Count / CRASH2_PLAYER_ANIM_SPEED) % CRASH2_PLAYER_PATTERN], TRUE);
}

//========================================================================
//コンストラクタ
//========================================================================
CPlayerCharge::CPlayerCharge(float x, float y)
	:CEffect(x, y, 0, 0, 0, 0), Time(0), Count(0)
{
	SEPlayerCharge = LoadSoundMem(CHARGE_PLAYER_SE);
	PlaySoundMem(SEPlayerCharge, DX_PLAYTYPE_BACK);

	LoadDivGraph(CHARGE_PLAYER_CHIP, CHARGE_PLAYER_PATTERN, 5, 3,
		CHARGE_PLAYER_SIZE_X, CHARGE_PLAYER_SIZE_Y, GHPlayerCharge);
}

//========================================================================
//移動
//========================================================================
bool CPlayerCharge::Move()
{
	Time++;
	Count++;

	if (!Game->PlayerChargeFlag) {
		return false;
	}

	return true;
}

//========================================================================
//描画
//========================================================================
void CPlayerCharge::Draw()
{
	DrawGraphF(X - (CHARGE_PLAYER_SIZE_X / 2) - 10, Y - (CHARGE_PLAYER_SIZE_Y / 2) - 15, GHPlayerCharge[(Count / CHARGE_PLAYER_ANIM_SPEED) % CHARGE_PLAYER_PATTERN], TRUE);
}

//========================================================================
//コンストラクタ
//========================================================================
CPlayerDeathblow::CPlayerDeathblow(float x, float y)
	:CEffect(x, y, -400, -500, 400, 500), Time(0), Count(0)
{
	SEPlayerDeathblow = LoadSoundMem(DEATHBLOW_PLAYER_SE);
	PlaySoundMem(SEPlayerDeathblow, DX_PLAYTYPE_BACK);

	LoadDivGraph(DEATHBLOW_PLAYER_CHIP, DEATHBLOW_PLAYER_PATTERN, 5, 5,
		DEATHBLOW_PLAYER_SIZE_X, DEATHBLOW_PLAYER_SIZE_Y, GHPlayerDeathblow);
}

//========================================================================
//移動
//========================================================================
bool CPlayerDeathblow::Move()
{
	Time++;
	Count++;

	if (Time >= 85) {
		//エフェクトを消す
		return false;
	}

	for (CRemTaskIter i(Game->EnemyList); i.HasNext();) {
		CEnemy* enemy = (CEnemy*)i.Next();

		if (Hit(enemy)) {
			enemy->Vit -= 1;
			Game->DefeatCount++;
		}
	}

	return true;
}

//========================================================================
//描画
//========================================================================
void CPlayerDeathblow::Draw()
{
	DrawRotaGraph3(320, 240, 320, 240, 1, 1, 0, GHPlayerDeathblow[(Count / DEATHBLOW_PLAYER_ANIM_SPEED) % DEATHBLOW_PLAYER_PATTERN], TRUE, FALSE);
}


//========================================================================
//コンストラクタ
//========================================================================
CEnemyCrash::CEnemyCrash(float x, float y)
	:CEffect(x, y, 0, 0, 0, 0), Time(0), Count(0)
{
	SEEnemyCrash = LoadSoundMem(CRASH_ENEMY_SE);
	PlaySoundMem(SEEnemyCrash, DX_PLAYTYPE_BACK);

	LoadDivGraph(CRASH_ENEMY_CHIP, CRASH_ENEMY_PATTERN, CRASH_ENEMY_PATTERN, 1,
		CRASH_ENEMY_SIZE_X, CRASH_ENEMY_SIZE_Y, GHEnemyCrash);
}

//========================================================================
//移動
//========================================================================
bool CEnemyCrash::Move()
{
	Time++;
	Count++;

	if (Time >= 85) {
		//エフェクトを消す
		return false;
	}
	return true;
}

//========================================================================
//描画
//========================================================================
void CEnemyCrash::Draw()
{
	DrawGraphF(X - (CRASH_ENEMY_SIZE_X / 2), Y - (CRASH_ENEMY_SIZE_Y / 2), GHEnemyCrash[(Count / CRASH_ENEMY_ANIM_SPEED) % CRASH_ENEMY_PATTERN], TRUE);
}
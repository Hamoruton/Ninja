#include "DxLib.h"
#include "Task2DACT.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Effect.h"
#include "Scene.h"
#include "UI.h"
#include <math.h>

//========================================================================
//コンストラクタ
//========================================================================
CPlayer::CPlayer(float x, float y)
	:CMover(Game->PlayerList, x, y, -26, -45, 26, 45), PlayerStatus(IDLE), Count(0), Speed(1.5f), VKeyFlag(true), BlueGaugeFlag(false), DeathblowFlag(false)
{
	//IDLE
	GHPlayerIdle[0] = LoadGraph("Sprites\\Player\\Idle__000.png");
	GHPlayerIdle[1] = LoadGraph("Sprites\\Player\\Idle__001.png");
	GHPlayerIdle[2] = LoadGraph("Sprites\\Player\\Idle__002.png");
	GHPlayerIdle[3] = LoadGraph("Sprites\\Player\\Idle__003.png");
	GHPlayerIdle[4] = LoadGraph("Sprites\\Player\\Idle__004.png");
	GHPlayerIdle[5] = LoadGraph("Sprites\\Player\\Idle__005.png");
	GHPlayerIdle[6] = LoadGraph("Sprites\\Player\\Idle__006.png");
	GHPlayerIdle[7] = LoadGraph("Sprites\\Player\\Idle__007.png");
	GHPlayerIdle[8] = LoadGraph("Sprites\\Player\\Idle__008.png");
	GHPlayerIdle[9] = LoadGraph("Sprites\\Player\\Idle__009.png");

	//RUN
	GHPlayerRun[0] = LoadGraph("Sprites\\Player\\Run__000.png");
	GHPlayerRun[1] = LoadGraph("Sprites\\Player\\Run__001.png");
	GHPlayerRun[2] = LoadGraph("Sprites\\Player\\Run__002.png");
	GHPlayerRun[3] = LoadGraph("Sprites\\Player\\Run__003.png");
	GHPlayerRun[4] = LoadGraph("Sprites\\Player\\Run__004.png");
	GHPlayerRun[5] = LoadGraph("Sprites\\Player\\Run__005.png");
	GHPlayerRun[6] = LoadGraph("Sprites\\Player\\Run__006.png");
	GHPlayerRun[7] = LoadGraph("Sprites\\Player\\Run__007.png");
	GHPlayerRun[8] = LoadGraph("Sprites\\Player\\Run__008.png");
	GHPlayerRun[9] = LoadGraph("Sprites\\Player\\Run__009.png");

	//JUMP
	GHPlayerJump[0] = LoadGraph("Sprites\\Player\\Jump__000.png");
	GHPlayerJump[1] = LoadGraph("Sprites\\Player\\Jump__001.png");
	GHPlayerJump[2] = LoadGraph("Sprites\\Player\\Jump__002.png");
	GHPlayerJump[3] = LoadGraph("Sprites\\Player\\Jump__003.png");
	GHPlayerJump[4] = LoadGraph("Sprites\\Player\\Jump__004.png");
	GHPlayerJump[5] = LoadGraph("Sprites\\Player\\Jump__005.png");
	GHPlayerJump[6] = LoadGraph("Sprites\\Player\\Jump__006.png");
	GHPlayerJump[7] = LoadGraph("Sprites\\Player\\Jump__007.png");
	GHPlayerJump[8] = LoadGraph("Sprites\\Player\\Jump__008.png");
	GHPlayerJump[9] = LoadGraph("Sprites\\Player\\Jump__009.png");

	//ATTACK
	GHPlayerAttack[0] = LoadGraph("Sprites\\Player\\Attack__000.png");
	GHPlayerAttack[1] = LoadGraph("Sprites\\Player\\Attack__001.png");
	GHPlayerAttack[2] = LoadGraph("Sprites\\Player\\Attack__002.png");
	GHPlayerAttack[3] = LoadGraph("Sprites\\Player\\Attack__003.png");
	GHPlayerAttack[4] = LoadGraph("Sprites\\Player\\Attack__004.png");
	GHPlayerAttack[5] = LoadGraph("Sprites\\Player\\Attack__005.png");
	GHPlayerAttack[6] = LoadGraph("Sprites\\Player\\Attack__006.png");
	GHPlayerAttack[7] = LoadGraph("Sprites\\Player\\Attack__007.png");
	GHPlayerAttack[8] = LoadGraph("Sprites\\Player\\Attack__008.png");
	GHPlayerAttack[9] = LoadGraph("Sprites\\Player\\Attack__009.png");

	//THROW
	GHPlayerThrow[0] = LoadGraph("Sprites\\Player\\Throw__000.png");
	GHPlayerThrow[1] = LoadGraph("Sprites\\Player\\Throw__001.png");
	GHPlayerThrow[2] = LoadGraph("Sprites\\Player\\Throw__002.png");
	GHPlayerThrow[3] = LoadGraph("Sprites\\Player\\Throw__003.png");
	GHPlayerThrow[4] = LoadGraph("Sprites\\Player\\Throw__004.png");
	GHPlayerThrow[5] = LoadGraph("Sprites\\Player\\Throw__005.png");
	GHPlayerThrow[6] = LoadGraph("Sprites\\Player\\Throw__006.png");
	GHPlayerThrow[7] = LoadGraph("Sprites\\Player\\Throw__007.png");
	GHPlayerThrow[8] = LoadGraph("Sprites\\Player\\Throw__008.png");
	GHPlayerThrow[9] = LoadGraph("Sprites\\Player\\Throw__009.png");

	//サウンド
	SEAttack = LoadSoundMem("Sounds\\Attack.mp3");
	SEJump = LoadSoundMem("Sounds\\Jump.mp3");
	SEMystery = LoadSoundMem("Sounds\\Mystery.mp3");
}

//========================================================================
//移動
//========================================================================
bool CPlayer::Move()
{
	//斜め移動の速度調整用定数
	static const float sqrt2 = (1.0f / (float)sqrt(2.0f));

	//ショットゲージとショット待機時間
	static const int ShotMaxGauge = SHOT_MAX_GAUGE, ShotMaxTime = SHOT_MAX_TIME;

	//移動範囲
	static const int MinX = PLAYER_CHIP_SIZE_X * PLAYER_REDUCTION / 2, MinY = PLAYER_CHIP_SIZE_Y * PLAYER_REDUCTION / 2;
	static const int MaxX = SCREEN_WIDTH - PLAYER_CHIP_SIZE_X * PLAYER_REDUCTION / 2;
	static const int MaxY = (SCREEN_HEIGHT - PLAYER_CHIP_SIZE_Y * PLAYER_REDUCTION / 2) - 30;

	//移動範囲の制限
	if (X < MinX) X = MinX;   else if (X > MaxX) X = MaxX;
	if (Y < MinY) Y = MinY;   else if (Y > MaxY) Y = MaxY;

	float vx = 0, vy = 0;

	//状態判定
	if (Y < MaxY) {
		PlayerStatus = JUMP;
		vy = GRAVITY / 2;
	}
	else {
		PlayerStatus = IDLE;
		VKeyFlag = false;
	}

	//入力処理
	if ((DeathblowFlag) && (Game->Key[KEY_INPUT_X])) 
	{
		PlaySoundMem(SEMystery, DX_PLAYTYPE_BACK);
		new CPlayerDeathblow(X, Y);
		Game->BlueGauge = 0;
		Game->BlueGaugePower = 0;
		DeathblowFlag = false;
	}
	else if (Game->Key[KEY_INPUT_X])
	{
		if ((!Game->PlayerChargeFlag) && (!VKeyFlag)) {
			new CPlayerCharge(X, Y);
			Game->PlayerChargeFlag = true;
			BlueGaugeFlag = true;
		}
		if ((BlueGaugeFlag) && (!VKeyFlag)) {
			PlayerStatus = IDLE;
			Game->BlueGaugePower++;
			Game->BlueGauge = Game->BlueGaugePower / 1800;
			if (Game->BlueGauge > MAX_BLUE_GAUGE)
				Game->BlueGauge = MAX_BLUE_GAUGE;
		}
	}
	else if (Game->Key[KEY_INPUT_LEFT]) 
	{
		if (Game->Key[KEY_INPUT_Z]) {
			ShotDirection = SHOT_LEFT;
			PlayerStatus = THROW_LEFT;
			if (ShotTime == 0) Shot();
		}
		else {
			PlayerStatus = RUN_LEFT;
			vx = -2.0f*Speed;
		}
	}
	else if (Game->Key[KEY_INPUT_RIGHT]) 
	{
		if (Game->Key[KEY_INPUT_Z]) {
			ShotDirection = SHOT_RIGHT;
			PlayerStatus = THROW_RIGHT;
			if (ShotTime == 0) Shot();
		}
		else {
			PlayerStatus = RUN_RIGHT;
			vx = 2.0f*Speed;
		}
	}else if (Game->Key[KEY_INPUT_UP]) 
	{
		if (Game->Key[KEY_INPUT_Z]) {
			ShotDirection = SHOT_UP;
			PlayerStatus = THROW_RIGHT;
			if (ShotTime == 0) Shot();
		}
	}
	else if (Game->Key[KEY_INPUT_Z]) 
	{
		PlayerStatus = THROW_RIGHT;
		ShotDirection = SHOT_RIGHT;
		if (ShotTime == 0) Shot();
	}
	else {
		if (ShotGauge > 0) {
			if (ShotTime == 0) Shot();
			ShotGauge--;
		}

		Game->PlayerChargeFlag = false;
		BlueGaugeFlag = false;

		if (Game->BlueGauge >= MAX_BLUE_GAUGE)
			DeathblowFlag = true;
	}

	if (Game->Key[KEY_INPUT_SPACE])
	{
		if (!VKeyFlag) {
			PlaySoundMem(SEJump, DX_PLAYTYPE_BACK);
			vy = -7 * 6 / 2 * GRAVITY;
			VKeyFlag = true;
		}
	}

	//ショットの待機時間を更新
	ShotTime = (ShotTime + 1) % ShotMaxTime;

	//斜め方向の速度調整
	/*if (vx != 0 && vy != 0) {
		vx *= sqrt2;
		vy *= sqrt2;
	}*/

	//移動
	X += (int)vx;
	Y += (int)vy;

	//アニメーションカウンタ
	Count++;

	return true;
}

//========================================================================
//描画
//========================================================================
void CPlayer::Draw()
{
	switch (PlayerStatus) {
	case IDLE:
		DrawRotaGraph3(X - (PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2), Y - (PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2), PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2, PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2,
			PLAYER_REDUCTION, PLAYER_REDUCTION, 0, GHPlayerIdle[(Count / PLAYER_IDLE_ANIM_SPEED) % PLAYER_IDLE_PATTERN], TRUE, FALSE);
		break;

	case RUN_RIGHT:
		DrawRotaGraph3(X - (PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2), Y - (PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2), PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2, PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2,
			PLAYER_REDUCTION, PLAYER_REDUCTION, 0, GHPlayerRun[(Count / PLAYER_RUN_ANIM_SPEED) % PLAYER_RUN_PATTERN], TRUE, FALSE);
		break;

	case RUN_LEFT:
		DrawRotaGraph3(X - (PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2), Y - (PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2), PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2, PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2,
			PLAYER_REDUCTION, PLAYER_REDUCTION, 0, GHPlayerRun[(Count / PLAYER_RUN_ANIM_SPEED) % PLAYER_RUN_PATTERN], TRUE, TRUE);
		break;

	case JUMP:
		DrawRotaGraph3(X - (PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2), Y - (PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2), PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2, PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2,
			PLAYER_REDUCTION, PLAYER_REDUCTION, 0, GHPlayerJump[(Count / PLAYER_JUMP_ANIM_SPEED) % PLAYER_JUMP_PATTERN], TRUE, FALSE);
		break;

	case ATTACK_RIGHT:
		DrawRotaGraph3(X - (PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2), Y - (PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2), PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2, PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2,
			PLAYER_REDUCTION, PLAYER_REDUCTION, 0, GHPlayerAttack[(Count / PLAYER_ATTACK_ANIM_SPEED) % PLAYER_ATTACK_PATTERN], TRUE, FALSE);
		break;

	case ATTACK_LEFT:
		DrawRotaGraph3(X - (PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2), Y - (PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2), PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2, PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2,
			PLAYER_REDUCTION, PLAYER_REDUCTION, 0, GHPlayerAttack[(Count / PLAYER_ATTACK_ANIM_SPEED) % PLAYER_ATTACK_PATTERN], TRUE, TRUE);
		break;

	case THROW_RIGHT:
		DrawRotaGraph3(X - (PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2), Y - (PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2), PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2, PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2,
			PLAYER_REDUCTION, PLAYER_REDUCTION, 0, GHPlayerThrow[(Count / PLAYER_ATTACK_ANIM_SPEED) % PLAYER_THROW_PATTERN], TRUE, FALSE);
		break;

	case THROW_LEFT:
		DrawRotaGraph3(X - (PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2), Y - (PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2), PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2, PLAYER_CHIP_SIZE_Y*PLAYER_REDUCTION / 2,
			PLAYER_REDUCTION, PLAYER_REDUCTION, 0, GHPlayerThrow[(Count / PLAYER_ATTACK_ANIM_SPEED) % PLAYER_THROW_PATTERN], TRUE, TRUE);
		break;
	}
}

//========================================================================
//ショットの発射
//========================================================================
void CPlayer::Shot()
{
	switch (ShotDirection) {
	case SHOT_RIGHT:
		new CShot(X, Y - 20, 30);
		new CShot(X, Y - 20, 0);
		new CShot(X, Y - 20, 330);
		break;

	case SHOT_LEFT:
		new CShot(X - 50, Y - 20, 150);
		new CShot(X - 50, Y - 20, 180);
		new CShot(X - 50, Y - 20, 210);
		break;

	case SHOT_UP:
		new CShot(X, Y - 20, 60);
		new CShot(X, Y - 20, 90);
		new CShot(X, Y - 20, 120);
		break;
	}
}

//========================================================================
//コンストラクタ
//========================================================================
CNormalPlayer::CNormalPlayer(float x, float y)
	:CPlayer(x, y), Vit(1) 
{
}

//========================================================================
//移動
//========================================================================
bool CNormalPlayer::Move() 
{
	if (Game->Gauge == 0) {
		return false;
	}
	if (Game->DefeatCount >= MAX_DEFEAT) {
		return false;
	}

	CPlayer::Move();

	//当たり判定処理(プレイヤーと弾)
	for (CRemTaskIter i(Game->BulletList); i.HasNext();) {
		CBullet* bullet = (CBullet*)i.Next();

		if (Hit(bullet)) {
			Vit--;
		}
		//爆発
		if (Vit <= 0) {
			new CPlayerCrash(X, Y);
			Game->Gauge--;
			return false;
		}
	}

	return true;
}

//========================================================================
//コンストラクタ
//========================================================================
CRevivalPlayer::CRevivalPlayer(float x, float y)
	:CPlayer(x, y), Time(0)
{
}

//========================================================================
//移動
//========================================================================
bool CRevivalPlayer::Move() 
{
	CPlayer::Move();

	Time++;
	if (Time > 120) {
		new CNormalPlayer(X, Y);
		return false;
	}
	return true;
}

//========================================================================
//描画
//========================================================================
void CRevivalPlayer::Draw() 
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	CPlayer::Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//========================================================================
//コンストラクタ
//========================================================================
CShot::CShot(float x, float y, float dir)
	:CMover(Game->ShotList, x, y), Count(0), Speed(SHOT_SPEED)
{
	GHShot = LoadGraph("Sprites\\Player\\shuriken.png");
	SEShot = LoadSoundMem("Sounds\\Throw.mp3");

	VX = cosf(DegToRad*dir)*Speed;
	VY = -sinf(DegToRad*dir)*Speed;

	PlaySoundMem(SEShot, DX_PLAYTYPE_BACK);
}

//========================================================================
//移動
//========================================================================
bool CShot::Move() 
{
	//移動
	X += VX;
	Y += VY;

	//アニメーションカウンタ
	Count++;

	for (CRemTaskIter i(Game->EnemyList); i.HasNext();) {
		CEnemy* enemy = (CEnemy*)i.Next();

		if (Hit(enemy)) {
			enemy->Vit -= 1;
			Game->DefeatCount++;
			return false;
		}
	}

	return !Out(SHOT_CHIP_SIZE_Y);
}

//========================================================================
//描画
//========================================================================
void CShot::Draw() 
{
	DrawRotaGraph3(X, Y, SHOT_CHIP_SIZE_X / 2, SHOT_CHIP_SIZE_Y / 2, SHOT_REDUCTION, SHOT_REDUCTION, Count / 5, GHShot, TRUE, FALSE);
}


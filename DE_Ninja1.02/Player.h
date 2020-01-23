#pragma once
#include "Mover.h"

#define PLAYER_REDUCTION   0.2
#define PLAYER_CHIP_SIZE_X 282
#define PLAYER_CHIP_SIZE_Y 464

//--------------------------------------------------------------------------
//IDLE
//--------------------------------------------------------------------------
#define PLAYER_IDLE_PATTERN      10
#define PLAYER_IDLE_ANIM_SPEED    3

//--------------------------------------------------------------------------
//RUN
//--------------------------------------------------------------------------
#define PLAYER_RUN_PATTERN      10
#define PLAYER_RUN_ANIM_SPEED    3

//--------------------------------------------------------------------------
//JUMP
//--------------------------------------------------------------------------
#define PLAYER_JUMP_PATTERN      10
#define PLAYER_JUMP_ANIM_SPEED   10

//--------------------------------------------------------------------------
//ATTACK
//--------------------------------------------------------------------------
#define PLAYER_ATTACK_PATTERN      10
#define PLAYER_ATTACK_ANIM_SPEED    1

//--------------------------------------------------------------------------
//THROW
//--------------------------------------------------------------------------
#define PLAYER_THROW_PATTERN      10
#define PLAYER_THROW_ANIM_SPEED    2


enum PLAYER_STATUS
{
	IDLE,
	RUN_RIGHT,
	RUN_LEFT,
	JUMP,
	ATTACK_RIGHT,
	ATTACK_LEFT,
	THROW_RIGHT,
	THROW_LEFT,
	DEAD,
	MAX
};

enum SHOT_DIRECTION 
{
	SHOT_RIGHT,
	SHOT_LEFT,
	SHOT_UP
};
static SHOT_DIRECTION ShotDirection;

//========================================================================
//プレイヤークラス
//========================================================================
class CPlayer 
	:public CMover
{
protected:
	int ShotGauge = 0, ShotTime = 0;

	void Shot();

public:
	PLAYER_STATUS PlayerStatus;
	
	//グラフィックハンドル
	int GHPlayerIdle[PLAYER_IDLE_PATTERN] = { 0 };
	int GHPlayerRun[PLAYER_RUN_PATTERN] = { 0 };
	int GHPlayerJump[PLAYER_JUMP_PATTERN] = { 0 };
	int GHPlayerAttack[PLAYER_ATTACK_PATTERN] = { 0 };
	int GHPlayerThrow[PLAYER_THROW_PATTERN] = { 0 };

	//サウンドハンドル
	int SEAttack;
	int SEJump;
	int SEMystery;

	int Count;
	float Speed;
	bool VKeyFlag;
	bool BlueGaugeFlag;
	bool DeathblowFlag;

	//コンストラクタ
	CPlayer(float x, float y);

	void* operator new(size_t t) {
		return operator_new(t, Game->PlayerList);
	}
	void operator delete(void* p) {
		operator_delete(p, Game->PlayerList);
	}

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};



//========================================================================
//プレイヤークラス(通常時)
//========================================================================
class CNormalPlayer
	:public CPlayer 
{
protected:
	//耐久力
	float Vit;
public:
	//コンストラクタ
	CNormalPlayer(float x, float y);

	//移動
	virtual bool Move();
};


//========================================================================
//プレイヤークラス(復活時)　(点滅して当たり判定なし)
//========================================================================
class CRevivalPlayer
	:public CPlayer 
{
protected:
	//耐久タイマー
	int Time;
public:
	//コンストラクタ
	CRevivalPlayer(float x, float y);

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

#define SHOT_MAX_GAUGE    15
#define SHOT_MAX_TIME     15

#define SHOT_REDUCTION   0.05
#define SHOT_CHIP_SIZE_X  640
#define SHOT_CHIP_SIZE_Y  640
#define SHOT_SPEED		    4

//========================================================================
//ショットクラス
//========================================================================
class CShot
	:public CMover 
{
public:
	//グラフィックハンドル
	int GHShot;

	//サウンドハンドル
	int SEShot;

	float VX, VY;
	float Speed;
	int Count;
	
	//コンストラクタ
	CShot(float x, float y, float dir);

	void* operator new(size_t t) {
		return operator_new(t, Game->ShotList);
	}
	void operator delete(void* p) {
		operator_delete(p, Game->ShotList);
	}

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};


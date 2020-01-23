#pragma once
#include "Mover.h"

//プレイヤーエフェクト
#define CRASH_PLAYER_CHIP      "Sprites\\Effect\\Slash.png"
#define CRASH_PLAYER_PATTERN       9
#define CRASH_PLAYER_SIZE_X      120
#define CRASH_PLAYER_SIZE_Y      120
#define CRASH_PLAYER_ANIM_SPEED   10
#define CRASH_PLAYER_SE        "Sounds\\Slash.mp3"

#define CRASH2_PLAYER_CHIP      "Sprites\\Effect\\Slash2.png"
#define CRASH2_PLAYER_PATTERN       8
#define CRASH2_PLAYER_SIZE_X      120
#define CRASH2_PLAYER_SIZE_Y      120
#define CRASH2_PLAYER_ANIM_SPEED   12
#define CRASH2_PLAYER_SE        "Sounds\\Slash.mp3"

#define CHARGE_PLAYER_CHIP      "Sprites\\Effect\\Charge.png"
#define CHARGE_PLAYER_PATTERN      15
#define CHARGE_PLAYER_SIZE_X      120
#define CHARGE_PLAYER_SIZE_Y      120
#define CHARGE_PLAYER_ANIM_SPEED    5
#define CHARGE_PLAYER_SE        "Sounds\\Charge.mp3"

#define DEATHBLOW_PLAYER_CHIP      "Sprites\\Effect\\Deathblow.png"
#define DEATHBLOW_PLAYER_PATTERN      22
#define DEATHBLOW_PLAYER_SIZE_X      640
#define DEATHBLOW_PLAYER_SIZE_Y      480
#define DEATHBLOW_PLAYER_ANIM_SPEED    5
#define DEATHBLOW_PLAYER_SE        "Sounds\\Deathblow.mp3"


//エネミーエフェクト
#define CRASH_ENEMY_CHIP      "Sprites\\Effect\\Expl.png"
#define CRASH_ENEMY_PATTERN    17
#define CRASH_ENEMY_SIZE_X     64
#define CRASH_ENEMY_SIZE_Y     64
#define CRASH_ENEMY_ANIM_SPEED  5
#define CRASH_ENEMY_SE        "Sounds\\Explosion.mp3"

//========================================================================
//エフェクトクラス
//========================================================================
class CEffect
	:public CMover 
{
public:
	//コンストラクタ
	CEffect(float x, float y, float l, float t, float r, float b)
		:CMover(Game->EffectList, x, y, l, t, r, b)
	{}

	void* operator new(size_t t) {
		return operator_new(t, Game->EffectList);
	}
	void operator delete(void* p) {
		operator_delete(p, Game->EffectList);
	}
};

//========================================================================
//爆発クラス(プレイヤー)
//========================================================================
class CPlayerCrash
	:public CEffect 
{
protected:
	//タイマー
	int Time;
	int Count;

public:
	//グラフィックハンドル
	int GHPlayerCrash[CRASH_PLAYER_PATTERN];
	//サウンドハンドル
	int SEPlayerCrash;

	//コンストラクタ
	CPlayerCrash(float x, float y);

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//爆発クラス2(プレイヤー)
//========================================================================
class CPlayerCrash2
	:public CEffect 
{
protected:
	//タイマー
	int Time;
	int Count;

public:
	//グラフィックハンドル
	int GHPlayerCrash2[CRASH2_PLAYER_PATTERN];
	//サウンドハンドル
	int SEPlayerCrash2;

	//コンストラクタ
	CPlayerCrash2(float x, float y);

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//チャージクラス(プレイヤー)
//========================================================================
class CPlayerCharge
	:public CEffect
{
protected:
	//タイマー
	int Time;
	int Count;

public:
	//グラフィックハンドル
	int GHPlayerCharge[CHARGE_PLAYER_PATTERN];
	//サウンドハンドル
	int SEPlayerCharge;

	//コンストラクタ
	CPlayerCharge(float x, float y);

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//必殺技クラス(プレイヤー)
//========================================================================
class CPlayerDeathblow
	:public CEffect
{
protected:
	//タイマー
	int Time;
	int Count;

public:
	//グラフィックハンドル
	int GHPlayerDeathblow[DEATHBLOW_PLAYER_PATTERN];
	//サウンドハンドル
	int SEPlayerDeathblow;

	//コンストラクタ
	CPlayerDeathblow(float x, float y);

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//爆発クラス(敵)
//========================================================================
class CEnemyCrash
	:public CEffect 
{
protected:
	//タイマー
	int Time;
	int Count;

public:
	//グラフィックハンドル
	int GHEnemyCrash[CRASH_ENEMY_PATTERN];
	//サウンドハンドル
	int SEEnemyCrash;

	//コンストラクタ
	CEnemyCrash(float x, float y);

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};



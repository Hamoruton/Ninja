#pragma once
#include "Mover.h"

//�v���C���[�G�t�F�N�g
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


//�G�l�~�[�G�t�F�N�g
#define CRASH_ENEMY_CHIP      "Sprites\\Effect\\Expl.png"
#define CRASH_ENEMY_PATTERN    17
#define CRASH_ENEMY_SIZE_X     64
#define CRASH_ENEMY_SIZE_Y     64
#define CRASH_ENEMY_ANIM_SPEED  5
#define CRASH_ENEMY_SE        "Sounds\\Explosion.mp3"

//========================================================================
//�G�t�F�N�g�N���X
//========================================================================
class CEffect
	:public CMover 
{
public:
	//�R���X�g���N�^
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
//�����N���X(�v���C���[)
//========================================================================
class CPlayerCrash
	:public CEffect 
{
protected:
	//�^�C�}�[
	int Time;
	int Count;

public:
	//�O���t�B�b�N�n���h��
	int GHPlayerCrash[CRASH_PLAYER_PATTERN];
	//�T�E���h�n���h��
	int SEPlayerCrash;

	//�R���X�g���N�^
	CPlayerCrash(float x, float y);

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//�����N���X2(�v���C���[)
//========================================================================
class CPlayerCrash2
	:public CEffect 
{
protected:
	//�^�C�}�[
	int Time;
	int Count;

public:
	//�O���t�B�b�N�n���h��
	int GHPlayerCrash2[CRASH2_PLAYER_PATTERN];
	//�T�E���h�n���h��
	int SEPlayerCrash2;

	//�R���X�g���N�^
	CPlayerCrash2(float x, float y);

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//�`���[�W�N���X(�v���C���[)
//========================================================================
class CPlayerCharge
	:public CEffect
{
protected:
	//�^�C�}�[
	int Time;
	int Count;

public:
	//�O���t�B�b�N�n���h��
	int GHPlayerCharge[CHARGE_PLAYER_PATTERN];
	//�T�E���h�n���h��
	int SEPlayerCharge;

	//�R���X�g���N�^
	CPlayerCharge(float x, float y);

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//�K�E�Z�N���X(�v���C���[)
//========================================================================
class CPlayerDeathblow
	:public CEffect
{
protected:
	//�^�C�}�[
	int Time;
	int Count;

public:
	//�O���t�B�b�N�n���h��
	int GHPlayerDeathblow[DEATHBLOW_PLAYER_PATTERN];
	//�T�E���h�n���h��
	int SEPlayerDeathblow;

	//�R���X�g���N�^
	CPlayerDeathblow(float x, float y);

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//�����N���X(�G)
//========================================================================
class CEnemyCrash
	:public CEffect 
{
protected:
	//�^�C�}�[
	int Time;
	int Count;

public:
	//�O���t�B�b�N�n���h��
	int GHEnemyCrash[CRASH_ENEMY_PATTERN];
	//�T�E���h�n���h��
	int SEEnemyCrash;

	//�R���X�g���N�^
	CEnemyCrash(float x, float y);

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};



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
//�v���C���[�N���X
//========================================================================
class CPlayer 
	:public CMover
{
protected:
	int ShotGauge = 0, ShotTime = 0;

	void Shot();

public:
	PLAYER_STATUS PlayerStatus;
	
	//�O���t�B�b�N�n���h��
	int GHPlayerIdle[PLAYER_IDLE_PATTERN] = { 0 };
	int GHPlayerRun[PLAYER_RUN_PATTERN] = { 0 };
	int GHPlayerJump[PLAYER_JUMP_PATTERN] = { 0 };
	int GHPlayerAttack[PLAYER_ATTACK_PATTERN] = { 0 };
	int GHPlayerThrow[PLAYER_THROW_PATTERN] = { 0 };

	//�T�E���h�n���h��
	int SEAttack;
	int SEJump;
	int SEMystery;

	int Count;
	float Speed;
	bool VKeyFlag;
	bool BlueGaugeFlag;
	bool DeathblowFlag;

	//�R���X�g���N�^
	CPlayer(float x, float y);

	void* operator new(size_t t) {
		return operator_new(t, Game->PlayerList);
	}
	void operator delete(void* p) {
		operator_delete(p, Game->PlayerList);
	}

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};



//========================================================================
//�v���C���[�N���X(�ʏ펞)
//========================================================================
class CNormalPlayer
	:public CPlayer 
{
protected:
	//�ϋv��
	float Vit;
public:
	//�R���X�g���N�^
	CNormalPlayer(float x, float y);

	//�ړ�
	virtual bool Move();
};


//========================================================================
//�v���C���[�N���X(������)�@(�_�ł��ē����蔻��Ȃ�)
//========================================================================
class CRevivalPlayer
	:public CPlayer 
{
protected:
	//�ϋv�^�C�}�[
	int Time;
public:
	//�R���X�g���N�^
	CRevivalPlayer(float x, float y);

	//�ړ��@�`��
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
//�V���b�g�N���X
//========================================================================
class CShot
	:public CMover 
{
public:
	//�O���t�B�b�N�n���h��
	int GHShot;

	//�T�E���h�n���h��
	int SEShot;

	float VX, VY;
	float Speed;
	int Count;
	
	//�R���X�g���N�^
	CShot(float x, float y, float dir);

	void* operator new(size_t t) {
		return operator_new(t, Game->ShotList);
	}
	void operator delete(void* p) {
		operator_delete(p, Game->ShotList);
	}

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};


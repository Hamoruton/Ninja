#pragma once

#include "Mover.h"

#define BULLET_REDUCTION   0.05
#define BULLET_CHIP_SIZE_X  640
#define BULLET_CHIP_SIZE_Y  640
#define BULLET_SPEED          4

//========================================================================
//�e�N���X
//========================================================================

class CBullet
	:public CMover 
{
public:
	//�O���t�B�b�N�n���h��
	int GHBullet;

	int Count;

	//�R���X�g���N�^
	CBullet(float x, float y);

	void* operator new(size_t t) {
		return operator_new(t, Game->BulletList);
	}
	void operator delete(void* p) {
		operator_delete(p, Game->BulletList);
	}

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//�����e�N���X
//========================================================================
class CDirBullet
	:public CBullet 
{
public:
	//���x�@�����x
	float VX, VY, AX, AY;

	//�R���X�g���N�^
	CDirBullet(float c, float y, float dir, float spd, float accel);

	//�ړ��@�`��
	virtual bool Move();
};

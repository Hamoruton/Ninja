#include "DxLib.h"
#include "Task2DACT.h"
#include "Bullet.h"
#include <math.h>

//========================================================================
//�R���X�g���N�^
//========================================================================
CBullet::CBullet(float x, float y)
	:CMover(Game->BulletList, x, y, -16, -16, 16, 16), Count(0)
{
	//�O���t�B�b�N�n���h��
	GHBullet = LoadGraph("Sprites\\Player\\shuriken.png");
}

//========================================================================
//�ړ�
//========================================================================
bool CBullet::Move() 
{
	Count++;

	return !Out(4);
}

//========================================================================
//�`��
//========================================================================
void CBullet::Draw() 
{
	DrawRotaGraph3(X - BULLET_CHIP_SIZE_X * BULLET_REDUCTION / 2, Y - BULLET_CHIP_SIZE_Y * BULLET_REDUCTION / 2,
		BULLET_CHIP_SIZE_X / 2, BULLET_CHIP_SIZE_Y / 2, BULLET_REDUCTION, BULLET_REDUCTION, Count / 5, GHBullet, TRUE, FALSE);
}

//========================================================================
//�R���X�g���N�^
//========================================================================
CDirBullet::CDirBullet(float x, float y, float dir, float spd, float accel)
	:CBullet(x, y)
{
	float c = cosf(DegToRad*dir), s = sinf(DegToRad*dir);
	//���x
	VX = spd * c;
	VY = spd * s;

	//�����x
	AX = accel * c;
	AY = accel * s;
}

//========================================================================
//�ړ�
//========================================================================
bool CDirBullet::Move() 
{
	//���W�X�V
	X += VX;
	Y += VY;

	//���x�X�V
	VX += AX;
	VY += AY;

	//�e�̋��ʏ���
	return CBullet::Move();
}
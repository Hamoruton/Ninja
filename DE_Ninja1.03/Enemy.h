#pragma once

#include "Mover.h"

//SCROLL
#define ENEMY_SCROLL_REDUCTION    0.3
#define ENEMY_SCROLL_CHIP_SIZE_X  367
#define ENEMY_SCROLL_CHIP_SIZE_Y  215

//========================================================================
//�G�N���X
//========================================================================
class CEnemy :public CMover 
{
protected:
	//�^�C�}�[
	int Time;

public:
	//�O���t�B�b�N�n���h��
	int GHEnemyScroll;

	//�ϋv�́@�X�R�A
	float Vit;
	int Score;

	//�R���X�g���N�^
	CEnemy(float x, float y, float l, float t, float r, float b, float vit, int score)
		:CMover(Game->EnemyList, x, y, l, t, r, b), Time(0), Vit(vit), Score(score) 
	{
	}

	void* operator new(size_t t) {
		return operator_new(t, Game->EnemyList);
	}
	void operator delete(void* p) {
		operator_delete(p, Game->EnemyList);
	}
};

//========================================================================
//���G�N���X
//========================================================================
class CSmallEnemy 
	:public CEnemy 
{
public:
	//�A�j���[�V�����J�E���^
	int Count;

	//�R���X�g���N�^
	CSmallEnemy(float x, float y);

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//���G�N���X
//========================================================================
class CSmallEnemy2
	:public CEnemy
{
public:
	//�A�j���[�V�����J�E���^
	int Count;

	//�R���X�g���N�^
	CSmallEnemy2(float x, float y);

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};


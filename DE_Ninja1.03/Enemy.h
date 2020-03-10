#pragma once

#include "Mover.h"

//SCROLL
#define ENEMY_SCROLL_REDUCTION    0.3
#define ENEMY_SCROLL_CHIP_SIZE_X  367
#define ENEMY_SCROLL_CHIP_SIZE_Y  215

//========================================================================
//敵クラス
//========================================================================
class CEnemy :public CMover 
{
protected:
	//タイマー
	int Time;

public:
	//グラフィックハンドル
	int GHEnemyScroll;

	//耐久力　スコア
	float Vit;
	int Score;

	//コンストラクタ
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
//小敵クラス
//========================================================================
class CSmallEnemy 
	:public CEnemy 
{
public:
	//アニメーションカウンタ
	int Count;

	//コンストラクタ
	CSmallEnemy(float x, float y);

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//小敵クラス
//========================================================================
class CSmallEnemy2
	:public CEnemy
{
public:
	//アニメーションカウンタ
	int Count;

	//コンストラクタ
	CSmallEnemy2(float x, float y);

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};


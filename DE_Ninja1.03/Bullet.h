#pragma once

#include "Mover.h"

#define BULLET_REDUCTION   0.05
#define BULLET_CHIP_SIZE_X  640
#define BULLET_CHIP_SIZE_Y  640
#define BULLET_SPEED          4

//========================================================================
//弾クラス
//========================================================================

class CBullet
	:public CMover 
{
public:
	//グラフィックハンドル
	int GHBullet;

	int Count;

	//コンストラクタ
	CBullet(float x, float y);

	void* operator new(size_t t) {
		return operator_new(t, Game->BulletList);
	}
	void operator delete(void* p) {
		operator_delete(p, Game->BulletList);
	}

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//方向弾クラス
//========================================================================
class CDirBullet
	:public CBullet 
{
public:
	//速度　加速度
	float VX, VY, AX, AY;

	//コンストラクタ
	CDirBullet(float c, float y, float dir, float spd, float accel);

	//移動　描画
	virtual bool Move();
};

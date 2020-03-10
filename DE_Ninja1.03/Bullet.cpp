#include "DxLib.h"
#include "Task2DACT.h"
#include "Bullet.h"
#include <math.h>

//========================================================================
//コンストラクタ
//========================================================================
CBullet::CBullet(float x, float y)
	:CMover(Game->BulletList, x, y, -16, -16, 16, 16), Count(0)
{
	//グラフィックハンドル
	GHBullet = LoadGraph("Sprites\\Player\\shuriken.png");
}

//========================================================================
//移動
//========================================================================
bool CBullet::Move() 
{
	Count++;

	return !Out(4);
}

//========================================================================
//描画
//========================================================================
void CBullet::Draw() 
{
	DrawRotaGraph3(X - BULLET_CHIP_SIZE_X * BULLET_REDUCTION / 2, Y - BULLET_CHIP_SIZE_Y * BULLET_REDUCTION / 2,
		BULLET_CHIP_SIZE_X / 2, BULLET_CHIP_SIZE_Y / 2, BULLET_REDUCTION, BULLET_REDUCTION, Count / 5, GHBullet, TRUE, FALSE);
}

//========================================================================
//コンストラクタ
//========================================================================
CDirBullet::CDirBullet(float x, float y, float dir, float spd, float accel)
	:CBullet(x, y)
{
	float c = cosf(DegToRad*dir), s = sinf(DegToRad*dir);
	//速度
	VX = spd * c;
	VY = spd * s;

	//加速度
	AX = accel * c;
	AY = accel * s;
}

//========================================================================
//移動
//========================================================================
bool CDirBullet::Move() 
{
	//座標更新
	X += VX;
	Y += VY;

	//速度更新
	VX += AX;
	VY += AY;

	//弾の共通処理
	return CBullet::Move();
}
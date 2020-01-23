#pragma once
#include "Mover.h"

//========================================================================
//UIクラス
//========================================================================
class CUI
	:public CMover
{
public:
	//コンストラクタ
	CUI() :CMover(Game->UIList, 0, 0)
	{
	}
	void* operator new(size_t t) {
		return operator_new(t, Game->UIList);
	}
	void operator delete(void* p) {
		operator_delete(p, Game->UIList);
	}
};

//BlackCover
#define GAUGE_REDUCTION   0.1
#define GAUGE_SIZE_X     1734
#define GAUGE_SIZE_Y      165

//GoldCover
#define GAUGE2_REDUCTION   0.1
#define GAUGE2_SIZE_X     1747
#define GAUGE2_SIZE_Y      178

//Gauge
#define MAX_GAUGE			  3
#define MAX_BLUE_GAUGE      0.1
#define GAUGE3_REDUCTION    0.1
#define GAUGE3_SIZE_X      1611
#define GAUGE3_SIZE_Y       113

//========================================================================
//体力クラス
//========================================================================
class CFitness
	:public CUI
{
public:
	//グラフィックハンドル
	int GHFitness[4];

	//サウンドハンドル

	//コンストラクタ
	CFitness();

	int Time;

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};



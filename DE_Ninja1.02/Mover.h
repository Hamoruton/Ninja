#pragma once
//-------------------------------------------------------------
#include "RemTask.h"

//=============================================================
// 移動物体クラス
//=============================================================
class CMover : public CRemTask {

public:
	// 座標
	float X, Y;

	// 当たり判定の左端・右端・上端・下端の相対座標
	float L, T, R, B;

	// コンストラクタ（当たり判定を指定する）
	CMover(
		CRemTaskList* task_list,
		float x, float y, float l, float t, float r, float b)
		: CRemTask(task_list), X(x), Y(y), L(l), T(t), R(r), B(b)
	{}
	// コンストラクタ（当たり判定を指定しない）
	CMover(CRemTaskList* task_list, float x, float y)
		: CRemTask(task_list), X(x), Y(y), L(0), T(0), R(0), B(0)
	{}

	// 移動、描画
	virtual bool Move() { return true; }
	virtual void Draw() {}

	// 画面外に出たかどうかの判定処理
	bool Out(float size) {
		return (
			X < (0 - size) || X >(SCREEN_WIDTH + size) ||
			Y < (0 - size) || Y >(SCREEN_HEIGHT + size)
			);
	}

	bool Hit(CMover* m) {
		return (
			(X + L) < (m->X + m->R) && (X + R) > (m->X + m->L) &&
			(Y + T) < (m->Y + m->B) && (Y + B) > (m->Y + m->T)
			);
	}

	bool Hit(CMover* m, float l, float t, float r, float b) {
		return (
			(X + l) < (m->X + m->R) && (X + r) > (m->X + m->L) &&
			(Y + t) < (m->Y + m->B) && (Y + b) > (m->Y + m->T)
			);
	}
};
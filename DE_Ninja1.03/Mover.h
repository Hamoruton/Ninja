#pragma once
//-------------------------------------------------------------
#include "RemTask.h"

//=============================================================
// �ړ����̃N���X
//=============================================================
class CMover : public CRemTask {

public:
	// ���W
	float X, Y;

	// �����蔻��̍��[�E�E�[�E��[�E���[�̑��΍��W
	float L, T, R, B;

	// �R���X�g���N�^�i�����蔻����w�肷��j
	CMover(
		CRemTaskList* task_list,
		float x, float y, float l, float t, float r, float b)
		: CRemTask(task_list), X(x), Y(y), L(l), T(t), R(r), B(b)
	{}
	// �R���X�g���N�^�i�����蔻����w�肵�Ȃ��j
	CMover(CRemTaskList* task_list, float x, float y)
		: CRemTask(task_list), X(x), Y(y), L(0), T(0), R(0), B(0)
	{}

	// �ړ��A�`��
	virtual bool Move() { return true; }
	virtual void Draw() {}

	// ��ʊO�ɏo�����ǂ����̔��菈��
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
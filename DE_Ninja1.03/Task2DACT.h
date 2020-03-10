#pragma once
#include "RemTask.h"

#define GRAVITY              9.8f
#define PI			  3.14159265f
#define RadToDeg     57.29577951f
#define DegToRad     0.017453293f

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_COLOR   32

#define FONT_FILE "Fonts\\njnaruto.ttf"
#define FONT_NAME "Ninja Naruto"

class CGame
{
public:
	//�O���t�B�b�N�n���h��
	int GHBack;

	//UI
	int   Gauge;
	float BlueGauge;
	float BlueGaugePower;
	bool  PlayerChargeFlag;

	int   DefeatCount;

	//����
	int Key[256] = { 0 };
	//�ꎞ��~
	bool Paused;
	//
	int Time = 0;

	//�R���X�g���N�^�@�f�X�g���N�^
	CGame();
	~CGame();

	//�Q�[���̐i�s
	void Run();
	//�ړ��@�`��
	virtual void Move();
	virtual void Draw();

	//�^�X�N���X�g
	CRemTaskList* PlayerList, *ShotList, *BulletList, *EnemyList, *EffectList, *SceneList, *UIList;
	void MoveTask(CRemTaskList* list);
	void DrawTask(CRemTaskList* list);
};

extern CGame* Game;

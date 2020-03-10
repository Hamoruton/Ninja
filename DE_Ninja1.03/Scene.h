#pragma once
#include "Mover.h"

//Title
#define TITLE_BACK           "Sprites\\BackGround\\BackGround.jpg"
#define TITLE_BACK_REDCUTION  0.6
#define TITLE_SIZE_X         1300
#define TITLE_SIZE_Y          800

#define TITLE_UI_BACK        "Sprites\\Player\\shuriken.png"
#define TITLE_SELECT_BACK    "Sprites\\BackGround\\Scroll.png"
#define TITLE_SE		     "Sounds\\Title.m4a"

//Ready
#define READY_SE     "Sounds\\Ready.mp3"

//Stage
#define MAX_DEFEAT 10

//GameOver
#define GAMEOVER_SE  "Sounds\\GameOver.mp3"

//GameClear
#define GAMECLEAR_SE "Sounds\\GameClear.mp3"

enum 
{
	MENU_START,
	MENU_EXIT,
	MENU_MAX
};

//========================================================================
//�V�[���N���X
//========================================================================
class CScene
	:public CMover 
{
public:
	//�R���X�g���N�^
	CScene() :CMover(Game->SceneList, 0, 0)
	{
	}
	void* operator new(size_t t) {
		return operator_new(t, Game->SceneList);
	}
	void operator delete(void* p) {
		operator_delete(p, Game->SceneList);
	}
};

//========================================================================
//�^�C�g���̃N���X
//========================================================================
class CTitle
	:public CScene 
{
public:
	//�O���t�B�b�N�n���h��
	int GHTitle[3];
	int GHTitlePlayer[10];
	//�T�E���h�n���h��
	int SETitleStart;
	int SETitleSelect;

	//���j���[���ڂ̑I���ʒu
	int MenuPos;

	//�R���X�g���N�^
	CTitle();

	int FadeColor;
	int Count;
	bool FadeFlag;
	bool KeyFlag;

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//������ʃN���X
//========================================================================
class CReady
	:public CScene 
{
protected:
	//�^�C�}�[
	int Time;

public:
	//�O���t�B�b�N�n���h��
	int GHReady;
	int GHReadyPlayer[10];
	//�T�E���h�n���h��
	int SEReady;

	//�R���X�g���N�^
	CReady();

	//�A�j���[�V�����J�E���^
	int Count;

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//�X�e�[�W�N���X
//========================================================================
class CStage
	:public CScene 
{
protected:
	//�^�C�}�[
	int Time;
	int Time2;

public:
	CStage();

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//�Q�[���I�[�o�[�N���X
//========================================================================
class CGameOver
	:public CScene
{
protected:
	//�^�C�}�[
	int Time;

public:
	//�O���t�B�b�N�n���h��
	int GHGameOverPlayer[10];
	//�T�E���h�n���h��
	int SEGameOver;

	//�R���X�g���N�^
	CGameOver();

	//�A�j���[�V�����J�E���^
	int Count;

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//�Q�[���N���A�N���X
//========================================================================
class CGameClear
	:public CScene
{
protected:
	//�^�C�}�[
	int Time;

public:
	//�O���t�B�b�N�n���h��
	int GHGameClearPlayer[10];
	//�T�E���h�n���h��
	int SEGameClear;

	//�R���X�g���N�^
	CGameClear();

	//�A�j���[�V�����J�E���^
	int Count;

	//�ړ��@�`��
	virtual bool Move();
	virtual void Draw();
};

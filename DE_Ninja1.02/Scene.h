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
//シーンクラス
//========================================================================
class CScene
	:public CMover 
{
public:
	//コンストラクタ
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
//タイトルのクラス
//========================================================================
class CTitle
	:public CScene 
{
public:
	//グラフィックハンドル
	int GHTitle[3];
	int GHTitlePlayer[10];
	//サウンドハンドル
	int SETitleStart;
	int SETitleSelect;

	//メニュー項目の選択位置
	int MenuPos;

	//コンストラクタ
	CTitle();

	int FadeColor;
	int Count;
	bool FadeFlag;
	bool KeyFlag;

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//準備画面クラス
//========================================================================
class CReady
	:public CScene 
{
protected:
	//タイマー
	int Time;

public:
	//グラフィックハンドル
	int GHReady;
	int GHReadyPlayer[10];
	//サウンドハンドル
	int SEReady;

	//コンストラクタ
	CReady();

	//アニメーションカウンタ
	int Count;

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//ステージクラス
//========================================================================
class CStage
	:public CScene 
{
protected:
	//タイマー
	int Time;
	int Time2;

public:
	CStage();

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//ゲームオーバークラス
//========================================================================
class CGameOver
	:public CScene
{
protected:
	//タイマー
	int Time;

public:
	//グラフィックハンドル
	int GHGameOverPlayer[10];
	//サウンドハンドル
	int SEGameOver;

	//コンストラクタ
	CGameOver();

	//アニメーションカウンタ
	int Count;

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

//========================================================================
//ゲームクリアクラス
//========================================================================
class CGameClear
	:public CScene
{
protected:
	//タイマー
	int Time;

public:
	//グラフィックハンドル
	int GHGameClearPlayer[10];
	//サウンドハンドル
	int SEGameClear;

	//コンストラクタ
	CGameClear();

	//アニメーションカウンタ
	int Count;

	//移動　描画
	virtual bool Move();
	virtual void Draw();
};

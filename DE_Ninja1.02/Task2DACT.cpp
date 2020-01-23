#include "DxLib.h"
#include "Task2DACT.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Effect.h"
#include "Scene.h"
#include "UI.h"

CGame* Game;

//========================================================================
//コンストラクタ
//========================================================================
CGame::CGame()
{
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);
	SetBackgroundColor(125, 125, 125);
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	PlayerList = new CRemTaskList(sizeof(CNormalPlayer), 10);
	ShotList = new CRemTaskList(sizeof(CShot), 100);
	BulletList = new CRemTaskList(sizeof(CDirBullet), 1000);
	EnemyList = new CRemTaskList(sizeof(CSmallEnemy), 100);
	EnemyList = new CRemTaskList(sizeof(CSmallEnemy2), 100);
	EffectList = new CRemTaskList(sizeof(CPlayerCrash), 100);
	EffectList = new CRemTaskList(sizeof(CEnemyCrash), 100);
	EffectList = new CRemTaskList(sizeof(CPlayerCharge), 100);
	EffectList = new CRemTaskList(sizeof(CPlayerDeathblow), 100);
	SceneList = new CRemTaskList(sizeof(CTitle), 10);
	UIList = new CRemTaskList(sizeof(CFitness), 10);

	LPCSTR FontPath = FONT_FILE;
	AddFontResourceEx(FontPath, FR_PRIVATE, NULL);
	ChangeFont(FONT_NAME, DX_CHARSET_DEFAULT);

	//グラフィックハンドル
	GHBack = LoadGraph(TITLE_BACK);

	//UI
	Gauge = MAX_GAUGE;
	BlueGauge = 0;
	BlueGaugePower = 0;
	PlayerChargeFlag = true;
	DefeatCount = 0;
}


//========================================================================
//デストラクタ
//========================================================================
CGame::~CGame()
{
	DxLib_End();
}


//========================================================================
//ゲームの実行
//========================================================================
void CGame::Run()
{
	while (!ProcessMessage())
	{
		ClearDrawScreen();

		char cTmpKey[256];
		GetHitKeyStateAll(cTmpKey);
		for (int i = 0; i < 256; i++) {
			if (cTmpKey[i] != 0) {
				Key[i]++;
			}
			else {
				Key[i] = 0;
			}
		}
		if (Key[KEY_INPUT_ESCAPE]) break;

		Game->Move();
		Game->Draw();

		ScreenFlip();
	}
}


//========================================================================
//移動
//========================================================================
void CGame::Move()
{
	Time++;

	//タスクの移動
	MoveTask(SceneList);
	MoveTask(PlayerList);
	MoveTask(ShotList);
	MoveTask(BulletList);
	MoveTask(EnemyList);
	MoveTask(EffectList);
	MoveTask(UIList);
}


//========================================================================
//描画
//========================================================================
void CGame::Draw()
{
	//背景
	DrawRotaGraph3(0, 0, 0, 0, TITLE_BACK_REDCUTION, TITLE_BACK_REDCUTION, 0, GHBack, TRUE, FALSE);

	//描画
	DrawTask(SceneList);
	DrawTask(PlayerList);
	DrawTask(ShotList);
	DrawTask(BulletList);
	DrawTask(EnemyList);
	DrawTask(EffectList);
	DrawTask(UIList);
}


//========================================================================
//タスクの動作
//========================================================================
void CGame::MoveTask(CRemTaskList* list)
{
	for (CRemTaskIter i(list); i.HasNext();) {
		CMover* mover = (CMover*)i.Next();
		if (!mover->Move())i.Remove();
	}
}

//========================================================================
//タスクの描画
//========================================================================
void CGame::DrawTask(CRemTaskList* list)
{
	for (CRemTaskIter i(list); i.HasNext();) {
		((CMover*)i.Next())->Draw();
	}
}

//========================================================================
//メインルーチン
//========================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game = new CGame();
	//ゲームの実行
	new CTitle();
	Game->Run();
	delete Game;
	return 0;
}
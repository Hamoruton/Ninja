#include "DxLib.h"
#include "Task2DACT.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"

//========================================================================
//タイトルクラス
//========================================================================
CTitle::CTitle()
	:MenuPos(MENU_START), Count(0), FadeColor(0), FadeFlag(false), KeyFlag(false)
{
	PlayMusic("Sounds\\Title.m4a", DX_PLAYTYPE_LOOP);
	SETitleStart = LoadSoundMem("Sounds\\Start.mp3");
	SETitleSelect = LoadSoundMem("Sounds\\Select.mp3");

	GHTitle[0] = LoadGraph(TITLE_BACK);
	GHTitle[1] = LoadGraph(TITLE_SELECT_BACK);
	GHTitle[2] = LoadGraph(TITLE_UI_BACK);

	//IDLE
	GHTitlePlayer[0] = LoadGraph("Sprites\\Player\\Throw__000.png");
	GHTitlePlayer[1] = LoadGraph("Sprites\\Player\\Throw__001.png");
	GHTitlePlayer[2] = LoadGraph("Sprites\\Player\\Throw__002.png");
	GHTitlePlayer[3] = LoadGraph("Sprites\\Player\\Throw__003.png");
	GHTitlePlayer[4] = LoadGraph("Sprites\\Player\\Throw__004.png");
	GHTitlePlayer[5] = LoadGraph("Sprites\\Player\\Throw__005.png");
	GHTitlePlayer[6] = LoadGraph("Sprites\\Player\\Throw__006.png");
	GHTitlePlayer[7] = LoadGraph("Sprites\\Player\\Throw__007.png");
	GHTitlePlayer[8] = LoadGraph("Sprites\\Player\\Throw__008.png");
	GHTitlePlayer[9] = LoadGraph("Sprites\\Player\\Throw__009.png");

	Game->DefeatCount = 0;
	Game->Gauge = MAX_GAUGE;
	Game->BlueGauge = 0;
	Game->BlueGaugePower = 0;
}

bool CTitle::Move() 
{
	if (Game->Key[KEY_INPUT_UP] == 1 && MenuPos > 0 && !KeyFlag) {
		PlaySoundMem(SETitleSelect, DX_PLAYTYPE_BACK);
		MenuPos--;
	}
	else if (Game->Key[KEY_INPUT_DOWN] == 1 && MenuPos < MENU_MAX - 1 && !KeyFlag) {
		PlaySoundMem(SETitleSelect, DX_PLAYTYPE_BACK);
		MenuPos++;
	}
	else if (Game->Key[KEY_INPUT_RETURN] && !KeyFlag) {
		switch (MenuPos) {
		case MENU_START:
			KeyFlag = true;
			FadeFlag = true;
			StopMusic();
			PlaySoundMem(SETitleStart, DX_PLAYTYPE_BACK);
			break;

		case MENU_EXIT:
			KeyFlag = true;
			PostQuitMessage(0);
			break;
		}
	}

	//フェードアウト
	if (FadeFlag) {
		FadeColor += 2;
		if (FadeColor == 256) {
			new CReady();
			return false;
		}
	}

	//アニメーションカウンタ
	Count++;

	return true;
}

void CTitle::Draw() 
{
	//背景
	DrawRotaGraph3(0, 0, 0, 0, TITLE_BACK_REDCUTION, TITLE_BACK_REDCUTION, 0, GHTitle[0], TRUE, FALSE);

	//Scroll
	switch (MenuPos) {
	case MENU_START:
		DrawRotaGraph3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 10, 0, 0, 0.5, 0.4, 0, GHTitle[1], TRUE, FALSE);
		break;

	case MENU_EXIT:
		DrawRotaGraph3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 70, 0, 0, 0.5, 0.4, 0, GHTitle[1], TRUE, FALSE);
		break;
	}
	DrawRotaGraph3(SCREEN_WIDTH / 2 - 170, SCREEN_HEIGHT / 2 - 190, 0, 0, 0.9, 0.6, 0, GHTitle[1], TRUE, FALSE);

	//Shuriken
	DrawRotaGraph3(530, 100, 320, 320, 0.4, 0.4, PI / 6, GHTitle[2], TRUE, FALSE);
	DrawRotaGraph3(100, 110, 320, 320, 0.35, 0.35, Count / 5, GHTitle[2], TRUE, FALSE);
	DrawRotaGraph3(140, 430, 320, 320, 0.3, 0.3, PI / 6, GHTitle[2], TRUE, FALSE);

	//Player
	DrawRotaGraph3(420, 220, 0, 0, 0.5, 0.5, 0, GHTitlePlayer[(Count / 8) % PLAYER_THROW_PATTERN], TRUE, TRUE);

	//文字列の描画
	SetFontSize(60);
	DrawString(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 150, "NINJA", GetColor(243, 152, 0));

	SetFontSize(32);
	DrawString(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 40, "START", (MenuPos == MENU_START ? GetColor(0, 0, 0) : GetColor(155, 155, 155)));
	DrawString(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 100, "EXIT", (MenuPos == MENU_EXIT ? GetColor(0, 0, 0) : GetColor(155, 155, 155)));
	
	//フェードアウト
	if (FadeFlag) {
		if (FadeColor >= 0 && FadeColor < 256)
			SetDrawBright(255 - FadeColor, 255 - FadeColor, 255 - FadeColor);
	}
}

//========================================================================
//準備クラス
//========================================================================
CReady::CReady()
	:Time(0), Count(0)
{
	SetDrawBright(255, 255, 255);
	
	SEReady = LoadSoundMem(READY_SE);
	PlaySoundMem(SEReady, DX_PLAYTYPE_BACK);

	//RUN
	GHReadyPlayer[0] = LoadGraph("Sprites\\Player\\Run__000.png");
	GHReadyPlayer[1] = LoadGraph("Sprites\\Player\\Run__001.png");
	GHReadyPlayer[2] = LoadGraph("Sprites\\Player\\Run__002.png");
	GHReadyPlayer[3] = LoadGraph("Sprites\\Player\\Run__003.png");
	GHReadyPlayer[4] = LoadGraph("Sprites\\Player\\Run__004.png");
	GHReadyPlayer[5] = LoadGraph("Sprites\\Player\\Run__005.png");
	GHReadyPlayer[6] = LoadGraph("Sprites\\Player\\Run__006.png");
	GHReadyPlayer[7] = LoadGraph("Sprites\\Player\\Run__007.png");
	GHReadyPlayer[8] = LoadGraph("Sprites\\Player\\Run__008.png");
	GHReadyPlayer[9] = LoadGraph("Sprites\\Player\\Run__009.png");
}

bool CReady::Move() 
{
	Time++;
	if (Time > 190) {
		new CStage();
		return false;
	}

	//アニメーションカウンタ
	Count++;

	return true;
}

void CReady::Draw() 
{
	//背景
	DrawRotaGraph3(0, 0, 0, 0, TITLE_BACK_REDCUTION, TITLE_BACK_REDCUTION, 0, Game->GHBack, TRUE, FALSE);

	//Player
	DrawRotaGraph3(100, 0, 0, 0, 1, 1, 0, GHReadyPlayer[(Count / 3) % 10], TRUE, FALSE);
}

//========================================================================
//ステージクラス
//========================================================================
CStage::CStage()
	:Time(0), Time2(0)
{
	new CNormalPlayer(PLAYER_CHIP_SIZE_X*PLAYER_REDUCTION / 2 + 50, SCREEN_HEIGHT / 2);
	new CFitness();
	PlayMusic("Sounds\\BGM.m4a", DX_PLAYTYPE_LOOP);
}

bool CStage::Move() 
{
	if (Game->DefeatCount >= MAX_DEFEAT) {
		Time2++;
		if (Time2 == 300) {
			new CGameClear();
			StopMusic();
			return false;
		}
	}

	if (Game->Gauge == 0) {
		new CGameOver();
		StopMusic();
		return false;
	}

	Time++;

	//敵の生成
	if (Time % 300 == 0) {
		int y = GetRand(100);
		new CSmallEnemy(680, y + ENEMY_SCROLL_CHIP_SIZE_Y * ENEMY_SCROLL_REDUCTION / 2);
	}
	if (Time % 400 == 0) {
		int y = GetRand(100);
		new CSmallEnemy2(-10, y * 3 + ENEMY_SCROLL_CHIP_SIZE_Y * ENEMY_SCROLL_REDUCTION / 2);
	}

	return true;
}

void CStage::Draw() 
{
	SetFontSize(32);
	DrawFormatString(500, 430, GetColor(255, 255, 255), "%2d / %2d", Game->DefeatCount, MAX_DEFEAT);
}

//========================================================================
//ゲームオーバークラス
//========================================================================
CGameOver::CGameOver()
	:Time(0), Count(0)
{
	SEGameOver = LoadSoundMem(GAMEOVER_SE);
	PlaySoundMem(SEGameOver, DX_PLAYTYPE_BACK);

	//RUN
	GHGameOverPlayer[0] = LoadGraph("Sprites\\Player\\Dead__000.png");
	GHGameOverPlayer[1] = LoadGraph("Sprites\\Player\\Dead__001.png");
	GHGameOverPlayer[2] = LoadGraph("Sprites\\Player\\Dead__002.png");
	GHGameOverPlayer[3] = LoadGraph("Sprites\\Player\\Dead__003.png");
	GHGameOverPlayer[4] = LoadGraph("Sprites\\Player\\Dead__004.png");
	GHGameOverPlayer[5] = LoadGraph("Sprites\\Player\\Dead__005.png");
	GHGameOverPlayer[6] = LoadGraph("Sprites\\Player\\Dead__006.png");
	GHGameOverPlayer[7] = LoadGraph("Sprites\\Player\\Dead__007.png");
	GHGameOverPlayer[8] = LoadGraph("Sprites\\Player\\Dead__008.png");
	GHGameOverPlayer[9] = LoadGraph("Sprites\\Player\\Dead__009.png");
}

bool CGameOver::Move()
{
	Time++;
	if (Time > 180) {
		new CTitle();
		return false;
	}

	//アニメーションカウンタ
	Count++;

	return true;
}

void CGameOver::Draw()
{
	//背景
	DrawRotaGraph3(0, 0, 0, 0, TITLE_BACK_REDCUTION, TITLE_BACK_REDCUTION, 0, Game->GHBack, TRUE, FALSE);

	//文字列
	SetFontSize(60);
	DrawString(160, 100, "GAMEOVER", GetColor(255, 0, 0));

	//Player
	if (Count > 90) {
		DrawRotaGraph3(100, -20, 0, 0, 1, 1, 0, GHGameOverPlayer[9], TRUE, FALSE);
	}
	else {
		DrawRotaGraph3(100, -20, 0, 0, 1, 1, 0, GHGameOverPlayer[(Count / 10) % 10], TRUE, FALSE);
	}
}

//========================================================================
//ゲームクリアクラス
//========================================================================
CGameClear::CGameClear()
	:Time(0), Count(0)
{
	SEGameClear = LoadSoundMem(GAMECLEAR_SE);
	PlaySoundMem(SEGameClear, DX_PLAYTYPE_BACK);

	//IDLE
	GHGameClearPlayer[0] = LoadGraph("Sprites\\Player\\Idle__000.png");
	GHGameClearPlayer[1] = LoadGraph("Sprites\\Player\\Idle__001.png");
	GHGameClearPlayer[2] = LoadGraph("Sprites\\Player\\Idle__002.png");
	GHGameClearPlayer[3] = LoadGraph("Sprites\\Player\\Idle__003.png");
	GHGameClearPlayer[4] = LoadGraph("Sprites\\Player\\Idle__004.png");
	GHGameClearPlayer[5] = LoadGraph("Sprites\\Player\\Idle__005.png");
	GHGameClearPlayer[6] = LoadGraph("Sprites\\Player\\Idle__006.png");
	GHGameClearPlayer[7] = LoadGraph("Sprites\\Player\\Idle__007.png");
	GHGameClearPlayer[8] = LoadGraph("Sprites\\Player\\Idle__008.png");
	GHGameClearPlayer[9] = LoadGraph("Sprites\\Player\\Idle__009.png");

	Game->PlayerChargeFlag = false;
}

bool CGameClear::Move()
{
	Time++;
	if (Time > 300) {
		new CTitle();
		return false;
	}

	//アニメーションカウンタ
	Count++;

	return true;
}

void CGameClear::Draw()
{
	//背景
	DrawRotaGraph3(0, 0, 0, 0, TITLE_BACK_REDCUTION, TITLE_BACK_REDCUTION, 0, Game->GHBack, TRUE, FALSE);

	//文字列
	SetFontSize(60);
	DrawString(350, 100, "GAME", GetColor(255, 204, 0));
	DrawString(380, 180, "CLEAR", GetColor(255, 204, 0));

	//Player
	DrawRotaGraph3(100, 45, 0, 0, 0.9, 0.9, 0, GHGameClearPlayer[(Count / 10) % 10], TRUE, FALSE);
	
}
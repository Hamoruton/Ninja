#include "DxLib.h"
#include "Task2DACT.h"
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"

//========================================================================
//コンストラクタ
//========================================================================
CFitness::CFitness()
	:Time(0)
{
	GHFitness[0] = LoadGraph("Sprites\\UI\\GaugeCover.png");
	GHFitness[1] = LoadGraph("Sprites\\UI\\GaugeCover2.png");
	GHFitness[2] = LoadGraph("Sprites\\UI\\GaugeBlue.png");
	GHFitness[3] = LoadGraph("Sprites\\UI\\GaugeGreen.png");
}

bool CFitness::Move()
{
	if (Game->Gauge == 0) {
		return false;
	}
	if (Game->DefeatCount >= MAX_DEFEAT) {
		Time++;
		if (Time == 120) {
			return false;
		}
	}

	return true;
}

void CFitness::Draw()
{
	switch (Game->Gauge) {
	case 3:
		DrawRotaGraph3(5, 5, 0, 0, GAUGE3_REDUCTION, GAUGE3_REDUCTION, 0, GHFitness[3], TRUE, FALSE);
		break;

	case 2:
		DrawRotaGraph3(5, 5, 0, 0, GAUGE3_REDUCTION * 2 / 3, GAUGE3_REDUCTION, 0, GHFitness[3], TRUE, FALSE);
		break;

	case 1:
		DrawRotaGraph3(5, 5, 0, 0, GAUGE3_REDUCTION / 3, GAUGE3_REDUCTION, 0, GHFitness[3], TRUE, FALSE);
		break;
	}
	DrawRotaGraph3(0, 0, 0, 0, GAUGE2_REDUCTION, GAUGE2_REDUCTION, 0, GHFitness[1], TRUE, FALSE);
	
	DrawRotaGraph3(5, 25, 0, 0, Game->BlueGauge, GAUGE3_REDUCTION, 0, GHFitness[2], TRUE, FALSE);
	DrawRotaGraph3(0, 20, 0, 0, GAUGE_REDUCTION, GAUGE_REDUCTION, 0, GHFitness[0], TRUE, FALSE);
}

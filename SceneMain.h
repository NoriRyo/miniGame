#pragma once
#include "SceneBase.h"
#include "Map.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();
	virtual void init()override;
	virtual SceneBase* update();
	virtual void draw();

	// 当たり判定
	int HitCheck(float mouseX, float mouseY);

	// マップチップの値を取得する関数
	int GetChipParam(float X, float Y);

private:

	int Goal;	// ゴールしたかどうか
	int MouseX, MouseY;	//　マウスの位置
	int keyPressed;	// キーが押されているかどうか
	int PrayerCollar;	//　プレイヤーの色
	int death;	//死んでいるかどうか
	float hsize;	//半分のサイズ
	// テキスト点滅用フレームカウント
	int m_textBlinkFrame;
	//int FrameCount; //フレームカウント
	Map p_map;
};
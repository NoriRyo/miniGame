#pragma once
#include "SceneBase.h"
#include "Map.h"
#include "warp.h"
class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();
	virtual void init()override;
	// 終了処理
	void end()override;
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

	int kIceBoxGraphic;
	int kIceBox1Graphic;
	int ksnowmoutianGraphic;
	int kPrayerGraphic;

	//int FrameCount; //フレームカウント
	int m_hWarpGraphic[warp::kWarpGraphicDivNum];
	Map p_map;
	warp m_pWarp;
};
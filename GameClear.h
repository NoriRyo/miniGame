#pragma once
#include "SceneBase.h"
class GameClear :  public SceneBase
{
public:
	GameClear()
	{
		m_hBg = -1;
		m_textBlinkFrame = 0;
		gameScreen = 0;
		effectScreen = 0;
		charX = 0;
		charY = 0;
		byteCount = 0;
		fontHandle = 0;
		sinRate = 0;
		TextSinRate = 0;
		tempSin = 0;
		Volume = 0;
		ClearBGMHandle = 0;
	}
	virtual ~GameClear() {}


	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;
private:
	// タイトル背景
	int m_hBg;

	int playerHandle;

	// テキスト点滅用フレームカウント
	int m_textBlinkFrame;
	// サウンド
	int ClearBGMHandle;

	int gameScreen;
	int effectScreen;

	int charX;
	int charY;

	int byteCount;

	int fontHandle;

	float sinRate;

	float TextSinRate;

	float tempSin;

	int Volume;
};


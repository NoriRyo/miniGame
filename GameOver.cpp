#include "GameOver.h"
#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "SceneMain.h"

namespace
{
	// 表示する文字列
	const char* const kTitleText = "GAMEOVER";
	const char* const kGuideText = "Click";
	// 文字列点滅
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;

	// 文字色
	const int kTitleFontColor = GetColor(255, 0, 0);

	const int kFontColor = GetColor(25, 25, 112);



}
GameOver::GameOver()
{
	m_hBg = -1;
	m_textBlinkFrame = 0;
	OBGMHandle = 0;
}
void GameOver::init()
{
	m_textBlinkFrame = 0;
	SetFontSize(32);
	m_hBg = LoadGraph("Data/OGB.png");
	// サウンド
	OBGMHandle = LoadSoundMem("sound/OBGM.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, OBGMHandle);
	PlaySoundMem(OBGMHandle, DX_PLAYTYPE_LOOP);
}

void GameOver::end()
{
	SetFontSize(16);
	DeleteSoundMem(OBGMHandle);
}

SceneBase* GameOver::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	// マウスカーソルを表示する
	SetMouseDispFlag(true);
	if (isFading())
	{
		bool isOut = isFadingOut();
		SceneBase::updateFade();
		// フェードアウト終了時にシーン切り替え
		if (!isFading() && isOut)
		{
			return (new SceneMain);
		}
	}
	// テキストの点滅
	m_textBlinkFrame++;
	if (m_textBlinkFrame >= kTextDispFrame + kTextHideFrame)
	{
		m_textBlinkFrame = 0;
	}
	if (!isFading())
	{
		if (padState & PAD_INPUT_1)
		{
			// フェードアウト開始
			startFadeOut();
		}
		
		// 左ボタンが押された
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			// フェードアウト開始
			startFadeOut();
		}
		
	}
	return this;
}

void GameOver::draw()
{
	DrawGraph(0, 0, m_hBg, false);
	SetFontSize(64);
	int width = GetDrawStringWidth(kTitleText, static_cast<int>(strlen(kTitleText)));
	DrawString(Game::kScreenWidth / 2 - width / 2, 160, kTitleText, kTitleFontColor);

	if (m_textBlinkFrame < kTextDispFrame)
	{
		SetFontSize(46);
		width = GetDrawStringWidth(kGuideText, static_cast<int>(strlen(kGuideText)));
		DrawString(Game::kScreenWidth / 2 - width / 2, 700, kGuideText, kFontColor);
	}
	SceneBase::drawFade();
}

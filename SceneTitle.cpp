#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "Pad.h"
#include "SceneMain.h"

namespace
{
	// 表示する文字列
	const char* const kTitleText = "イライラ棒ゲーム【ラッシュ】Rush";
	const char* const kGuideText = "Click";
	// 文字列点滅
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;

	// 文字色
	const int kTitleFontColor = GetColor(255, 0, 0);

	const int kFontColor = GetColor(255, 255, 255);

}

void SceneTitle::init()
{
	m_textBlinkFrame = 0;
	SetFontSize(32);

	m_hBg = LoadGraph("Data/BG.png");
	m_hTg = LoadGraph("Data/iraira.png");

	// サウンド
	TitleBGMHandle = LoadSoundMem("sound/TBGM.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, TitleBGMHandle);
	PlaySoundMem(TitleBGMHandle, DX_PLAYTYPE_LOOP);

	ClickSoundHandle = LoadSoundMem("sound/Click.wav");
	ChangeVolumeSoundMem(255 * 80 / 100, ClickSoundHandle);
	
}

void SceneTitle::end()
{
	SetFontSize(16);
	DeleteSoundMem(TitleBGMHandle);
	DeleteSoundMem(ClickSoundHandle);
}

SceneBase* SceneTitle::update()
{
	//return (new SceneMain);
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
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			// フェードアウト開始
			startFadeOut();
		}
		// 左ボタンが押された
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			PlaySoundMem(ClickSoundHandle, DX_PLAYTYPE_BACK);
			// フェードアウト開始
			startFadeOut();
		}
	}
	return this;
}

void SceneTitle::draw()
{
	DrawGraph(0, 0, m_hBg, false);
	DrawGraph(64, 160, m_hTg, true);

	int width = GetDrawStringWidth(kTitleText, static_cast<int>(strlen(kTitleText)));
	//DrawString(Game::kScreenWidth / 2 - width / 2, 160, kTitleText, kTitleFontColor);

	if (m_textBlinkFrame < kTextDispFrame)
	{
		width = GetDrawStringWidth(kGuideText, static_cast<int>(strlen(kGuideText)));
		DrawString(Game::kScreenWidth / 2 - width / 2, 580, kGuideText, kFontColor);
	}

	SceneBase::drawFade();
}

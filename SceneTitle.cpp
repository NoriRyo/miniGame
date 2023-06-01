#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "Pad.h"
#include "SceneMain.h"

namespace
{
	// �\�����镶����
	const char* const kTitleText = "�C���C���_�Q�[���y���b�V���zRush";
	const char* const kGuideText = "Click";
	// ������_��
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;

	// �����F
	const int kTitleFontColor = GetColor(255, 0, 0);

	const int kFontColor = GetColor(255, 255, 255);

}

void SceneTitle::init()
{
	m_textBlinkFrame = 0;
	SetFontSize(32);

	m_hBg = LoadGraph("Data/BG.png");
}

void SceneTitle::end()
{
	SetFontSize(16);
}

SceneBase* SceneTitle::update()
{
	//return (new SceneMain);
	if (isFading())
	{
		bool isOut = isFadingOut();
		SceneBase::updateFade();
		// �t�F�[�h�A�E�g�I�����ɃV�[���؂�ւ�
		if (!isFading() && isOut)
		{
			return (new SceneMain);
		}
	}
	// �e�L�X�g�̓_��
	m_textBlinkFrame++;
	if (m_textBlinkFrame >= kTextDispFrame + kTextHideFrame)
	{
		m_textBlinkFrame = 0;
	}
	if (!isFading())
	{
		if (Pad::isTrigger(PAD_INPUT_1))
		{
			// �t�F�[�h�A�E�g�J�n
			startFadeOut();
		}
		// ���{�^���������ꂽ
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			// �t�F�[�h�A�E�g�J�n
			startFadeOut();
		}
	}
	return this;
}

void SceneTitle::draw()
{
	DrawGraph(0, 0, m_hBg, false);

	int width = GetDrawStringWidth(kTitleText, static_cast<int>(strlen(kTitleText)));
	DrawString(Game::kScreenWidth / 2 - width / 2, 160, kTitleText, kTitleFontColor);

	if (m_textBlinkFrame < kTextDispFrame)
	{
		width = GetDrawStringWidth(kGuideText, static_cast<int>(strlen(kGuideText)));
		DrawString(Game::kScreenWidth / 2 - width / 2, 280, kGuideText, kFontColor);
	}

	SceneBase::drawFade();
}

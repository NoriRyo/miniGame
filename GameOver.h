#pragma once
#include "SceneBase.h"
class GameOver : public SceneBase
{
public:
	GameOver();
	virtual ~GameOver() {}


	virtual void init() override;
	virtual void end() override;

	virtual SceneBase* update() override;
	virtual void draw() override;

private:
	// �^�C�g���w�i
	int m_hBg;

	// �e�L�X�g�_�ŗp�t���[���J�E���g
	int m_textBlinkFrame;
};


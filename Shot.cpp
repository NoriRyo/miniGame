#include "Shot.h"
#include "Game.h"
#include "DxLib.h"

Shot::Shot()
{
	// �L�����N�^�[�̃T�C�Y
	constexpr int kSizeX = 48;
	constexpr int kSizeY = 48;
	// �L�����N�^�[�A�j���[�V����1�R�}������
	constexpr int kAinmeChangeFrame = 8;

	int GHandle;
}

Shot::~Shot()
{
	// ������
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
}

void Shot::init() 
{
}

void Shot::update()
{
}

void Shot::draw()
{
}

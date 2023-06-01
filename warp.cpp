#include "warp.h"
#include "Game.h"
#include "DxLib.h"

namespace
{
	// �L�����N�^�[�̃T�C�Y
	constexpr int kSizeX = 48;
	constexpr int kSizeY = 48;
	// �L�����N�^�[�A�j���[�V����1�R�}������
	constexpr int kAinmeChangeFrame = 8;

	constexpr int m_fieldX((Game::kScreenWidth / 2) / 2);
	constexpr int m_fieldY(124);
	int GHandle;

}
warp::warp()
{
	// ������
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_animeNo = 0;
	m_animeFrame = 0;
	m_dirNo = 0;
}



void warp::init()
{
	m_animeNo = 0;
	m_animeFrame = 0;
	m_dirNo = 0;
}

void warp::Update()
{
	m_animeFrame++;
	if (m_animeFrame >= kGraphicDivX * kAinmeChangeFrame)
	{
		m_animeFrame = 0;
	}
	
	int tenpAnimeNo = m_animeFrame / kAinmeChangeFrame;
	m_animeNo = m_dirNo * kGraphicDivX + tenpAnimeNo;
}
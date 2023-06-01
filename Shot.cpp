#include "Shot.h"
#include "Game.h"
#include "DxLib.h"

Shot::Shot()
{
	// キャラクターのサイズ
	constexpr int kSizeX = 48;
	constexpr int kSizeY = 48;
	// キャラクターアニメーション1コマあたり
	constexpr int kAinmeChangeFrame = 8;

	int GHandle;
}

Shot::~Shot()
{
	// 初期化
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

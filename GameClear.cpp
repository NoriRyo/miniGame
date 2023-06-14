#include "GameClear.h"
#include "DxLib.h"
#include "game.h"
#include "SceneTitle.h"
#include "Vec2.h"
#include <string>

namespace
{
	// 表示する文字列
	const char* const kTitleText = "GAMECLEAR";
	const char* const kAText = "A->TITLE";
	//const char* const kBText = "B->Return";
	// 文字列点滅
	constexpr int kTextDispFrame = 60;
	constexpr int kTextHideFrame = 15;

	// 文字色
	const int kTitleFontColor = GetColor(0, 0, 255);

	const int kFontColorA = GetColor(0, 255, 0);
	const int kFontColorB = GetColor(0, 0, 255);

	int Titleback = true;

	int Fieldback = true;


	constexpr int kParticleNum = 256;

	Vec2 pos[kParticleNum];
	Vec2 vec[kParticleNum];
}
void GameClear::init()
{
	m_textBlinkFrame = 0;
	SetFontSize(64);
	// サウンド
	ClearBGMHandle = LoadSoundMem("sound/CBGM.wav");
	ChangeVolumeSoundMem(255 * 50 / 100, ClearBGMHandle);
	PlaySoundMem(ClearBGMHandle, DX_PLAYTYPE_LOOP);

	// フォント
	fontHandle = CreateFontToHandle("Showcard Gothic", 120, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);


	SetAlwaysRunFlag(true);

	sinRate = 0.0f;
	gameScreen = LoadGraph("data/kk.png");
	playerHandle = LoadGraph("data/pHappy.png");

	effectScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	for (int i = 0; i < kParticleNum; i++)
	{
		pos[i].x = GetRand(Game::kScreenWidth);
		pos[i].y = -GetRand(Game::kScreenHeight);

		vec[i].x = 0.0f;
		vec[i].y = GetRand(20) + 20;
		vec[i].y /= 10.0f;
	}

	charX = 0;
	charY = 0;
	TextSinRate = 0.0f;

	byteCount = 0;	// 表示するバイト数に変換する
}

void GameClear::end()
{
	SetFontSize(16);
	//DeleteGraph(gameScreen);
	DeleteGraph(effectScreen);
	DeleteGraph(playerHandle);
	DeleteGraph(ClearBGMHandle);
}

SceneBase* GameClear::update()
{
	if (Volume <= 100)
	{
		Volume++;
	}
	for (int i = 0; i < kParticleNum; i++)
	{
		pos[i] += vec[i];
		if (pos[i].y > Game::kScreenHeight)
		{
			pos[i].x = GetRand(Game::kScreenWidth);
			pos[i].y = 0.0f;

			vec[i].x = 0.0f;
			vec[i].y = GetRand(20) + 20;
			vec[i].y /= 10.0f;
		}
	}
	sinRate += 0.05f;

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (isFading())
	{
		bool isOut = isFadingOut();
		SceneBase::updateFade();
		// フェードアウト終了時にシーン切り替え
		if (!isFading() && isOut)
		{
			DeleteSoundMem(ClearBGMHandle);
		
			return (new SceneTitle);
		}
	}
	// テキストの点滅
	m_textBlinkFrame++;
	if (m_textBlinkFrame >= 100)
	{
		m_textBlinkFrame = 0;
	}
	if (!isFading())
	{
		// 左ボタンが押された
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			// フェードアウト開始
			startFadeOut();
		}
	}

	TextSinRate += 0.05f;

	return this;
}

void GameClear::draw()
{
	SetDrawScreen(effectScreen);
	ClearDrawScreen();
	BeginAADraw();
	for (int i = 0; i < kParticleNum; i++)
	{
		float rate = (vec[i].length() / 4.0f);
		//	DrawCircleAA(pos[i].x, pos[i].y, 4 * rate, 32, 0x808020, true);
			// 遠くのもの(落下速度が遅いもの)は小さく、暗く描画する
		DrawCircleAA(pos[i].x, pos[i].y, 4 * rate, 32, GetColor(255 * rate, 255 * rate, 255 * rate), true);
	}
	EndAADraw();
	SetDrawScreen(DX_SCREEN_BACK);
	// 画面のクリア
	ClearDrawScreen();
	
	DrawGraph(0, 0, gameScreen, true);
	

	//加算合成する
	SetDrawBlendMode(DX_BLENDMODE_ADD, 192);

	DrawGraph(0, 0, effectScreen, true);
	//画面をぼかす
	GraphFilter(effectScreen, DX_GRAPH_FILTER_GAUSS, 16, 800);
	for (int i = 0; i < 8; i++)
	{
		DrawGraph(GetRand(4) - 2, GetRand(4) - 2, effectScreen, false);
	}

	GraphFilter(effectScreen, DX_GRAPH_FILTER_GAUSS, 32, 2400);
	for (int i = 0; i < 8; i++)
	{
		DrawGraph(GetRand(8) - 4, GetRand(8) - 4, effectScreen, false);
	}
	//元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	byteCount = 0;	// 表示するバイト数に変換する

	std::string temp = kTitleText;
	int width = GetDrawStringWidth(kTitleText, static_cast<int>(strlen(kTitleText)));
	charX = Game::kScreenWidth / 2 - width / 2 - 160;
	charY = 300;

	SetFontSize(64);

	//// でか
	//int width1= GetDrawStringWidth(kTitleText, static_cast<int>(strlen(kTitleText)));
	//DrawString(Game::kScreenWidth / 2 - width1 / 2, 160, kTitleText, kTitleFontColor);

	tempSin = TextSinRate;


	//// しょ
	//int width2 = GetDrawStringWidth(kAText, static_cast<int>(strlen(kAText)));
	//DrawString(Game::kScreenWidth / 2 - width2 / 2, 580, kAText, kFontColorA);
	
	
	// キャラクター
	DrawGraph(0, 150, playerHandle, true);



	while (1)
	{
		if (byteCount > temp.size())	break;
		unsigned char charData = temp[byteCount];	// チェックする文字
		int size = 0;
		if (charData < 0x80)
		{
			size = 1;
		}
		else
		{
			size = 2;
		}
		int moveX = -36;
		int moveY = sinf(tempSin) * 16.0f;
		tempSin += DX_PI_F;

		DrawStringToHandle(charX + moveX + 2, charY + moveY + 2, temp.substr(byteCount, size).c_str(), 0xffffff, fontHandle);
		DrawStringToHandle(charX + moveX, charY + moveY, temp.substr(byteCount, size).c_str(), 0xffff00, fontHandle);
		charX += GetDrawStringWidthToHandle(temp.substr(byteCount, size).c_str(), size, fontHandle);
		byteCount += size;

	}
	
	SceneBase::drawFade();
}

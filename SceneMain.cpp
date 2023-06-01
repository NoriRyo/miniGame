#include "SceneMain.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneBase.h"
#include "GameOver.h"
#include "GameClear.h"

namespace
{
	// マップ情報
	constexpr int kMapSizeX = 16;
	constexpr int kMapSizeY = 16;

	// 壁
	constexpr int kWall = 1;
	// 割れた壁
	constexpr int kCrackedWall = 3;
	// 壁
	constexpr int kEmpty = 0;
	// ゴール
	constexpr int kGoal = 2;
	// 壁に当たった
	constexpr int kHit = 5;
	// 割れた壁に当たった
	constexpr int kCrackedHit = 7;
	// ゴールに当たった
	constexpr int kGoalHit = 6;
	// サイズ
	constexpr float kSize = 48.0f;
	// サイズ
	constexpr float PlayerkSize = 30.0f;

	const char* const kGuideText = "Click";

	// 文字列点滅
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;

	const int kFontColor = GetColor(255, 255, 255);

	//// マップ
	//constexpr int kMapData[kMapSizeY][kMapSizeX] =
	//{
	//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	//	{1,0,0,0,0,0,0,0,0,0,0,0,0,2,2,1},
	//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	//};
}

SceneMain::SceneMain() :
	keyPressed(),
	MouseX(),
	MouseY(),
	PrayerCollar(),
	death(),
	hsize(),
	Goal()
	//FrameCount()
{
}
SceneMain::~SceneMain()
{
}
void SceneMain::init()
{
	//プレイヤーの色
	PrayerCollar = 0xfffffff;
	//キーが押されたかどうか
	keyPressed = false;
	//死んでいるかどうか
	death = true;
	//半分のサイズ
	hsize = PlayerkSize * 0.5f;
	//マウスの位置
	MouseX = 0;
	MouseY = 0;
	Goal = true;
	m_textBlinkFrame = 0;
}
SceneBase* SceneMain::update()
{
	clsDx();
	p_map.update();
	//int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1)
	if (CheckHitKey(KEY_INPUT_3))
	{
		p_map.StageNumber = 15;
	}

	
	// 死んでいたらGameOverへ
	if (death == false)
	{
		keyPressed = false;
		return(new GameOver);
	}

	// ゴールしたら次のステージへ
	if (Goal == false)
	{
		Goal = true;
		p_map.StageNumber ++;
	}

	// クリアへ
	if (p_map.StageNumber >= 25)
	{
		keyPressed = false;
		return(new GameClear);
	}

	//printfDx("St = %d", p_map.StageNumber);
	//printfDx("Fc = %d", FrameCount);

	// マウスカーソルを表示する
	SetMouseDispFlag(true);
	if (keyPressed == true)
	{
		//マウスの位置を取得する
		GetMousePoint(&MouseX, &MouseY);

		// マウスカーソルを非表示にする
		SetMouseDispFlag(false);

		// 左上のチェック
		HitCheck(MouseX - hsize, MouseY - hsize);
		// 右上のチェック
		HitCheck(MouseX + hsize, MouseY - hsize);
		// 左下のチェック
		HitCheck(MouseX - hsize, MouseY + hsize);
		// 右下のチェック
		HitCheck(MouseX + hsize, MouseY + hsize);

	}
	
	//マウスの左クリックを取得する
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		PrayerCollar = 0xfff00ff;
		keyPressed = true;
	}

	// テキストの点滅
	m_textBlinkFrame++;
	if (m_textBlinkFrame >= kTextDispFrame + kTextHideFrame)
	{
		m_textBlinkFrame = 0;
	}

	return this;
}
void SceneMain::draw()
{
	DrawBox(0,0, 1000,1000, 0xffffff,true);
	int kIceBoxGraphic = LoadGraph("data/IceBox.png");
	int kIceBox1Graphic = LoadGraph("data/IceBox1.png");
	int ksnowmoutianGraphic = LoadGraph("data/snowmoutian.png");
	int kPrayerGraphic = LoadGraph("data/py.png");
	DrawExtendGraph(0, 0,1000,1000, ksnowmoutianGraphic, true);
	//マップの描画
	for (int x = 0; x < kMapSizeX; x++)
	{
		for (int y = 0; y < kMapSizeY; y++)
		{
			if (p_map.kMapData[y][x] == kWall)
			{
				DrawGraph(x * kSize,y * kSize, kIceBoxGraphic, TRUE);
			}
			if (p_map.kMapData[y][x] == 3)
			{
				DrawGraph(x * kSize, y * kSize, kIceBox1Graphic, TRUE);
			}
			if (p_map.kMapData[y][x] == kGoal)
			{
				DrawBox(x * kSize, y * kSize,
					x * kSize + kSize, y * kSize + kSize, 0xffff00, true);
			}
		}
	}
	if (keyPressed == false)
	{
		if (m_textBlinkFrame < kTextDispFrame)
		{
			int width = GetDrawStringWidth(kGuideText, static_cast<int>(strlen(kGuideText)));
			DrawString(768 / 2 - width / 2, 280, kGuideText, kFontColor);
		}
	}
	
	//プレイヤーの描画
	//DrawBox(MouseX - hsize, MouseY - hsize, 
	//	MouseX + PlayerkSize - hsize, MouseY + PlayerkSize - hsize, PrayerCollar, true);
	if (p_map.StageNumber == 9 || p_map.StageNumber == 17)
	{
		DrawGraph(MouseX - hsize, MouseY - hsize, kPrayerGraphic, TRUE);
	}
	else
	{
		DrawTurnGraph(MouseX - hsize, MouseY - hsize, kPrayerGraphic, TRUE);
	}
}

int SceneMain::HitCheck(float mouseX, float mouseY)
{
	//マップチップの値を取得する
	if (GetChipParam(mouseX, mouseY) == kHit)
	{
		//もし壁にぶつかっていたら
		PrayerCollar = 0xff0000;

		death = false;

		return 5;
	}
	if (GetChipParam(mouseX, mouseY) == kGoalHit)
	{
		//もしゴールにぶつかっていたら
		Goal = false;
		return 5;
	}

	if (GetChipParam(mouseX, mouseY) == kCrackedHit)
	{
		//もしにぶつかっていたら
		return 5;
	}

	return 0;
}

int SceneMain::GetChipParam(float X, float Y)
{
	int x, y;
	// 整数値へ変換
	x = (int)X / kSize;
	y = (int)Y / kSize;
	if (p_map.kMapData[y][x] == kWall)
	{
		return kHit;
	}
	if (p_map.kMapData[y][x] == kGoal)
	{
		return kGoalHit;
	}
	if (p_map.kMapData[y][x] == kCrackedWall)
	{
		//p_map.kMapData[y][x] = 0;
		//return kCrackedHit;
	}
	return 0;
}

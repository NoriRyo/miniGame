#include "SceneMain.h"
#include "DxLib.h"
#include "SceneTitle.h"
#include "SceneBase.h"
#include "GameOver.h"
#include "GameClear.h"
#include "warp.h"
namespace
{
	// �}�b�v���
	constexpr int kMapSizeX = 16;
	constexpr int kMapSizeY = 16;

	// ��
	constexpr int kWall = 1;
	// ���ꂽ��
	constexpr int kCrackedWall = 3;
	// ��
	constexpr int kEmpty = 0;
	// �S�[��
	constexpr int kGoal = 2;
	// �ǂɓ�������
	constexpr int kHit = 5;
	// ���ꂽ�ǂɓ�������
	constexpr int kCrackedHit = 7;
	// �S�[���ɓ�������
	constexpr int kGoalHit = 6;
	// �T�C�Y
	constexpr float kSize = 48.0f;
	// �T�C�Y
	constexpr float PlayerkSize = 30.0f;

	const char* const kGuideText = "Click";

	// ������_��
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;

	const int kFontColor = GetColor(255, 255, 255);

	const char* const kWarpGraphicFilename = "data/warp.png";


	// �}�b�v
	constexpr int kMapData[kMapSizeY][kMapSizeX] =
	{

		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,3,3,1},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,3,3,1},
		{1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1},
		{1,2,2,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,2,2,0,0,0,0,0,0,0,0,0,0,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

	};
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
	for (auto& WarpHandle : m_hWarpGraphic)
	{
		WarpHandle = -1;
	}
}
SceneMain::~SceneMain()
{
}
void SceneMain::init()
{
	//�v���C���[�̐F
	PrayerCollar = 0xfffffff;
	//�L�[�������ꂽ���ǂ���
	keyPressed = false;
	//����ł��邩�ǂ���
	death = true;
	//�����̃T�C�Y
	hsize = PlayerkSize * 0.5f;
	//�}�E�X�̈ʒu
	MouseX = 0;
	MouseY = 0;
	Goal = true;
	m_textBlinkFrame = 0;

	LoadDivGraph(kWarpGraphicFilename, warp::kWarpGraphicDivNum,
		warp::kGraphicDivX, warp::kGraphicDivY,
		warp::kGraphicSizeX, warp::kGraphicSizeY, m_hWarpGraphic);

	for (int i = 0; i < warp::kWarpGraphicDivNum; i++)
	{
		m_pWarp.setHandle(i, m_hWarpGraphic[i]);
	}

	kIceBoxGraphic = LoadGraph("data/IceBox.png");
	kIceBox1Graphic = LoadGraph("data/IceBox1.png");
	ksnowmoutianGraphic = LoadGraph("data/snowmoutian.png");
	kPrayerGraphic = LoadGraph("data/py.png");

	m_pWarp.init();
}
void SceneMain::end()
{
	for (auto& handle : m_hWarpGraphic)
	{
		DeleteGraph(m_hWarpGraphic[2]);
	}
}
SceneBase* SceneMain::update()
{
	clsDx();
	p_map.update();
	m_pWarp.Update();
	//int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1)
	if (CheckHitKey(KEY_INPUT_3))
	{
		p_map.StageNumber = 15;
	}

	
	// ����ł�����GameOver��
	if (death == false)
	{
		keyPressed = false;
		return(new GameOver);
	}

	// �S�[�������玟�̃X�e�[�W��
	if (Goal == false)
	{
		Goal = true;
		p_map.StageNumber ++;
	}

	// �N���A��
	if (p_map.StageNumber >= 25)
	{
		keyPressed = false;
		return(new GameClear);
	}

	//printfDx("St = %d", p_map.StageNumber);
	//printfDx("Fc = %d", FrameCount);

	// �}�E�X�J�[�\����\������
	SetMouseDispFlag(true);
	if (keyPressed == true)
	{
		//�}�E�X�̈ʒu���擾����
		GetMousePoint(&MouseX, &MouseY);

		// �}�E�X�J�[�\�����\���ɂ���
		SetMouseDispFlag(false);

		// ����̃`�F�b�N
		HitCheck(MouseX - hsize, MouseY - hsize);
		// �E��̃`�F�b�N
		HitCheck(MouseX + hsize, MouseY - hsize);
		// �����̃`�F�b�N
		HitCheck(MouseX - hsize, MouseY + hsize);
		// �E���̃`�F�b�N
		HitCheck(MouseX + hsize, MouseY + hsize);

	}
	
	//�}�E�X�̍��N���b�N���擾����
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		PrayerCollar = 0xfff00ff;
		keyPressed = true;
	}

	// �e�L�X�g�̓_��
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
	
	DrawExtendGraph(0, 0,1000,1000, ksnowmoutianGraphic, true);
	//�}�b�v�̕`��
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
				//DrawBox(x * kSize, y * kSize,
				//	x * kSize + kSize, y * kSize + kSize, 0xffff00, true);
				DrawGraph(x * kSize, y * kSize, m_pWarp.m_handle[m_pWarp.m_animeNo], true);

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
	else
	{
#if false

		//�v���C���[�̕`��
		DrawBox(MouseX - hsize, MouseY - hsize,
			MouseX + PlayerkSize - hsize, MouseY + PlayerkSize - hsize, PrayerCollar, true);

#else

		if (p_map.StageNumber == 9 || p_map.StageNumber == 17)
		{
			DrawGraph(MouseX - hsize, MouseY - hsize, kPrayerGraphic, TRUE);
		}
		else
		{
			DrawTurnGraph(MouseX - hsize, MouseY - hsize, kPrayerGraphic, TRUE);
		}
#endif
	}


}

int SceneMain::HitCheck(float mouseX, float mouseY)
{
	//�}�b�v�`�b�v�̒l���擾����
	if (GetChipParam(mouseX, mouseY) == kHit)
	{
		//�����ǂɂԂ����Ă�����
		PrayerCollar = 0xff0000;

		death = false;

		return 5;
	}
	if (GetChipParam(mouseX, mouseY) == kGoalHit)
	{
		//�����S�[���ɂԂ����Ă�����
		Goal = false;
		return 5;
	}

	if (GetChipParam(mouseX, mouseY) == kCrackedHit)
	{
		//�����ɂԂ����Ă�����
		return 5;
	}

	return 0;
}

int SceneMain::GetChipParam(float X, float Y)
{
	int x, y;
	// �����l�֕ϊ�
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
		p_map.kMapData[y][x] = 0;
		return kCrackedHit;
	}
	return 0;
}

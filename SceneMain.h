#pragma once
#include "SceneBase.h"
#include "Map.h"
#include "warp.h"
class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();
	virtual void init()override;
	// �I������
	void end()override;
	virtual SceneBase* update();
	virtual void draw();

	// �����蔻��
	int HitCheck(float mouseX, float mouseY);

	// �}�b�v�`�b�v�̒l���擾����֐�
	int GetChipParam(float X, float Y);

private:

	int Goal;	// �S�[���������ǂ���
	int MouseX, MouseY;	//�@�}�E�X�̈ʒu
	int keyPressed;	// �L�[��������Ă��邩�ǂ���
	int PrayerCollar;	//�@�v���C���[�̐F
	int death;	//����ł��邩�ǂ���
	float hsize;	//�����̃T�C�Y
	// �e�L�X�g�_�ŗp�t���[���J�E���g
	int m_textBlinkFrame;

	int kIceBoxGraphic;
	int kIceBox1Graphic;
	int ksnowmoutianGraphic;
	int kPrayerGraphic;

	//int FrameCount; //�t���[���J�E���g
	int m_hWarpGraphic[warp::kWarpGraphicDivNum];
	Map p_map;
	warp m_pWarp;
};
#pragma once
class Shot
{
public:
	// �萔��`

	//�O���t�B�b�N������
	static constexpr int kGraphicDivX = 4;
	static constexpr int kGraphicDivY = 1;
	static constexpr int kDoorGraphicDivNum = kGraphicDivX * kGraphicDivY;

	//�O���t�B�b�N�T�C�Y
	static constexpr int kGraphicSizeX = 48;
	static constexpr int kGraphicSizeY = 48;
public:
	Shot();
	virtual ~Shot();
	void init();
	void update();
	void draw();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	float x;
	float y;

	int m_handle[kDoorGraphicDivNum];

	// �L�����N�^�[�̃A�j���[�V����
	int m_animeNo;	//�@�\������ԍ�
	int m_animeFrame; // �t���[��
};


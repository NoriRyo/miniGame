#pragma once
class warp
{
public:
	// �萔��`

	// �O���t�B�b�N������
	static constexpr int kGraphicDivX = 5;
	static constexpr int kGraphicDivY = 3;
	static constexpr int kWarpGraphicDivNum = kGraphicDivX * kGraphicDivY;

	// �O���t�B�b�N�T�C�Y
	static constexpr int kGraphicSizeX = 48;
	static constexpr int kGraphicSizeY = 48;
public:
	warp();
	virtual ~warp(){};
	void init();
	void Update();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	float x;
	float y;

	int m_handle[kWarpGraphicDivNum];

	// �L�����N�^�[�̃A�j���[�V����
	int m_animeNo;	//�@�\������ԍ�
	int m_animeFrame;
	int m_dirNo;	// �i�s����
private:
	// �T�E���h�n���h��
	int warpSHandle;
};


#pragma once
class Map
{
public:
	Map();
	virtual ~Map();
	virtual void init();
	virtual void update();
	virtual void draw();
	int kMapData[16][16];
	int StageNumber;	//�X�e�[�W�ԍ�

private:
};


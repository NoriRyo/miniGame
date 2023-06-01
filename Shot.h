#pragma once
class Shot
{
public:
	// 定数定義

	//グラフィック分割数
	static constexpr int kGraphicDivX = 4;
	static constexpr int kGraphicDivY = 1;
	static constexpr int kDoorGraphicDivNum = kGraphicDivX * kGraphicDivY;

	//グラフィックサイズ
	static constexpr int kGraphicSizeX = 48;
	static constexpr int kGraphicSizeY = 48;
public:
	Shot();
	virtual ~Shot();
	void init();
	void update();
	void draw();

	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	float x;
	float y;

	int m_handle[kDoorGraphicDivNum];

	// キャラクターのアニメーション
	int m_animeNo;	//　表示する番号
	int m_animeFrame; // フレーム
};


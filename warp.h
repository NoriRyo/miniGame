#pragma once
class warp
{
public:
	// 定数定義

	// グラフィック分割数
	static constexpr int kGraphicDivX = 5;
	static constexpr int kGraphicDivY = 3;
	static constexpr int kWarpGraphicDivNum = kGraphicDivX * kGraphicDivY;

	// グラフィックサイズ
	static constexpr int kGraphicSizeX = 48;
	static constexpr int kGraphicSizeY = 48;
public:
	warp();
	virtual ~warp(){};
	void init();
	void Update();

	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	float x;
	float y;

	int m_handle[kWarpGraphicDivNum];

	// キャラクターのアニメーション
	int m_animeNo;	//　表示する番号
	int m_animeFrame;
	int m_dirNo;	// 進行方向
private:
	// サウンドハンドル
	int warpSHandle;
};


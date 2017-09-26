#include "Obj3d.h"


#include <vector>

#pragma once


class RandomMapMaker
{
private:
	//　シード値
	float seedX;
	float seedZ;

	//　マップのサイズ
	float width;
	float depth;

	//　高さの最大値
	int MaxHeight;

	//　起伏の激しさ
	float relif;

	//　マップのサイズ
	float MapSize;

	// 箱モデル
	std::vector<Obj3d>	m_cube;

public:
	//　初期化
	RandomMapMaker();

	void SetY(float y);

	void Draw();

	
};

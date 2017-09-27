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
	int width;
	int depth;


	//　高さの最大値
	int MaxHeight;

	//　起伏の激しさ
	float relif;

	// 箱モデル
	std::vector<Obj3d>	m_cube;

public:
	//　初期化
	RandomMapMaker();

	void MakeY(int number);

	// 初期化
	void Initialize();

	//　更新処理
	void Update();

	//　行列更新
	void Calc();

	//　描画
	void Draw();

};

#include "Obj3d.h"
#include "PerlinNoise.hpp"
#include "VertexCube.h"

#include <vector>


#pragma once


class RandomMapMaker
{
public:


private:
	//　シード値
	float seedX;
	float seedZ;

	//　マップのサイズ
	int width;
	int depth;


	//　高さの最大値
	int MaxHeight;

	int RandomHeighit;

	int y;

	//　起伏の激しさ
	float relief;

	// 箱モデル
	std::vector<Obj3d>	m_cube;

	siv::PerlinNoise m_noise;

	std::vector<std::unique_ptr<VertexCube>> m_VertexCube;

public:
	//　初期化
	RandomMapMaker();

	float MakeY(int x, int z);

	// 初期化
	void Initialize();

	//　更新処理
	void Update();

	//　行列更新
	void Calc();

	//　描画
	void Draw();

};

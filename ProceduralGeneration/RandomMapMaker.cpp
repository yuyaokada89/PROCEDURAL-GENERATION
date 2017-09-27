
#include <random>
#include <ctime>

#include "RandomMapMaker.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

RandomMapMaker::RandomMapMaker()
{
	srand((unsigned int)time(NULL));

	seedX = 0;
	seedZ = 0;

	width = 35;
	depth = 35;

	MaxHeight = 5;

	seedX = rand() * 100.0f;
	seedZ = rand() * 100.0f;

	m_cube.resize(width * depth);

	Initialize();
}

//―――――――――――――――――――――――
//初期化
//
//
//―――――――――――――――――――――――
void RandomMapMaker::Initialize()
{
	//　キューブ生成
	for (int i = 0; i < width*depth; i++)
	{
		Vector3 pos = Vector3(i / width, 0, i % depth);

		//キューブ作成
		m_cube[i].SetTranslation(pos);
		MakeY(i);

		if (m_cube[i].GetTranslation().y >= 3)
		{
			m_cube[i].LoadModel(L"cmo/Grassy.cmo");
		}
		else if (m_cube[i].GetTranslation().y == 2)
		{
			m_cube[i].LoadModel(L"cmo/Sand.cmo");
		}
		else if (m_cube[i].GetTranslation().y == 1)
		{
			m_cube[i].LoadModel(L"cmo/Water.cmo");
		}
		else if (m_cube[i].GetTranslation().y == 0)
		{
			m_cube[i].LoadModel(L"cmo/Stone.cmo");
		}
	}
}


//―――――――――――――――――――――――
//更新処理
//
//
//―――――――――――――――――――――――
void RandomMapMaker::Update()
{
	Calc();
}


//
//
//
void RandomMapMaker::Calc()
{
	for (int i = 0; i < width * depth; i++)
	{
		m_cube[i].Update();
	}
}

//
//
//
//
void RandomMapMaker::MakeY(int number)
{
	int y = rand() % MaxHeight;
	Vector3 localPos = Vector3(m_cube[number].GetTranslation().x, y, m_cube[number].GetTranslation().z);
	m_cube[number].SetTranslation(localPos);
}


//
//
//
//
void RandomMapMaker::Draw()
{
	// 全箱分描画
	for (int i = 0; i < width * depth; i++)
	{
		m_cube[i].Draw();
	}
}
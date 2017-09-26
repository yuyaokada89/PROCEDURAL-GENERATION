
#include <random>

#include "RandomMapMaker.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

RandomMapMaker::RandomMapMaker()
{
	seedX = 0;
	seedZ = 0;

	width = 50;
	depth = 50;

	MaxHeight = 5;

	MapSize = 1.f;

	Vector3 map = Vector3(MapSize, MapSize, MapSize);

	seedX = rand() * 100.0f;
	seedZ = rand() * 100.0f;

	m_cube.resize(width*depth);

	//　キューブ生成
	for (int x = 0; x < width; x++)
	{
		for (int z = 0; z < depth; z++)
		{
			Vector3 pos = Vector3(x, 0, z);

			//キューブ作成
			m_cube[x + z].LoadModel(L"cmo/Sand.cmo");
			m_cube[x + z].SetTranslation(pos);

			SetY(m_cube[x + z].GetTranslation().y);

		}
	}
}

void RandomMapMaker::SetY(float y)
{
	float _y = 0;

	_y = rand() % MaxHeight;

	for (int x = 0; x < width; x++)
	{
		for (int z = 0; z < depth; z++)
		{
			Vector3 localPos = Vector3(m_cube[x + z].GetTranslation().x, _y, m_cube[x + z].GetTranslation().z);
			m_cube[x + z].SetTranslation(localPos);

		}
	}
}

void RandomMapMaker::Draw()
{
	// 全箱分描画
	for (int x = 0; x < width; x++)
	{
		for (int z = 0; z < depth; z++)
		{
			m_cube[x+z].Draw();
		}
	}
}
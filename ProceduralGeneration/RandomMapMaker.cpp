
#include <random>
#include <ctime>
#include <d3d11.h>

#include "DXTKGroup.h"
#include "RandomMapMaker.h"
#include "MemoryLeakDetector.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;



RandomMapMaker::RandomMapMaker(bool changeflag)
{
	srand((unsigned int)time(NULL));

	DrawChangeFlag = changeflag;

	seedX = 0;
	seedZ = 0;

	width = 40;
	depth = 40;

	MaxHeight = 10;

	relief = 15.0f;

	m_cube.resize(width * depth);

	//SetUpMemoryLeakDetector();

	Initialize();
}

//―――――――――――――――――――――――
//初期化
//
//
//―――――――――――――――――――――――
void RandomMapMaker::Initialize()
{
	seedX = rand() % 100;
	seedZ = rand() % 100;

	m_VertexCube.resize(width * depth);
	
	for (int i = 0; i < width * depth; i++)
	{
		Matrix world;

		//　スケーリング行列
		Matrix scalemat = Matrix::CreateScale(Vector3(1, 1, 1));

		Vector3 pos = Vector3(i / width, MakeY(i / width, i % depth), i % depth);

		//　平行移動行列
		Matrix transmat = Matrix::CreateTranslation(pos);

		//　ワールド行列を合成
		world = scalemat * transmat;

		Vector4 color;


		if (DrawChangeFlag)
		{
			if (MakeY(i / width, i % depth) >= 2)
			{
				m_cube[i].LoadModel(L"cmo/Grassy.cmo");
			}
			else if (MakeY(i / width, i % depth) >= 0)
			{
				m_cube[i].LoadModel(L"cmo/Sand.cmo");
			}
			else if (MakeY(i / width, i % depth) >= -3)
			{
				m_cube[i].LoadModel(L"cmo/Water.cmo");
			}
			else if (MakeY(i / width, i % depth) >= -6)
			{
				m_cube[i].LoadModel(L"cmo/Stone.cmo");
			}
			m_cube[i].SetTranslation(pos);
		}
		else
		{
			if (MakeY(i / width, i % depth) >= 2)
			{
				color = Vector4(Colors::Green);
			}
			else if (MakeY(i / width, i % depth) >= 0)
			{
				color = Vector4(Colors::SaddleBrown);
			}
			else if (MakeY(i / width, i % depth) >= -3)
			{
				color = Vector4(Colors::RoyalBlue);
			}
			else if (MakeY(i / width, i % depth) >= -6)
			{
				color = Vector4(Colors::Gray);
			}
			m_VertexCube[i] = std::make_unique<VertexCube>(world, color);
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
	if (!DrawChangeFlag)
	{
		for (std::vector<std::unique_ptr<VertexCube>>::iterator it = m_VertexCube.begin();
			it != m_VertexCube.end();
			it++)
		{
			(*it)->Update();
		}
	}

	Calc();
}


//
//
//
void RandomMapMaker::Calc()
{
	if (DrawChangeFlag)
	{
		for (int i = 0; i < width * depth; i++)
		{
			m_cube[i].Update();
		}
	}
}

//
//
//
//
float RandomMapMaker::MakeY(int x,int z)
{
	float xSample = (x + seedX) / relief;
	float zSample = (z + seedZ) / relief;

	float noise = m_noise.noise(xSample, zSample);

	y = MaxHeight * noise;
	return y;
}


//
//
//
//
void RandomMapMaker::Draw()
{
	if (!DrawChangeFlag)
	{
		for (std::vector<std::unique_ptr<VertexCube>>::iterator it = m_VertexCube.begin();
			it != m_VertexCube.end();
			it++)
		{
			(*it)->Render();
		}
	}
	else
	{
		for (int i = 0; i < width * depth; i++)
		{
			m_cube[i].Draw();
		}
	}

}


//

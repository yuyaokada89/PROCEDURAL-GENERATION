
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

	//SetUpMemoryLeakDetector();

	Initialize();
}

RandomMapMaker::~RandomMapMaker()
{
	Finalize();
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
	m_cube.resize(width * depth);
	
	for (int i = 0; i < width * depth; i++)
	{
		Matrix world;

		Vector4 color;

		float y;

		y = MakeY(i / width, i % depth);

		//　スケーリング行列
		Matrix scalemat = Matrix::CreateScale(Vector3(1, 1, 1));

		pos = Vector3(i / width, y, i % depth);

		//　平行移動行列
		Matrix transmat = Matrix::CreateTranslation(pos);

		//　ワールド行列を合成
		world = scalemat * transmat;


		if (DrawChangeFlag)
		{
			m_cube[i] = std::make_unique<Obj3d>();
			if (y >= 2)
			{
				m_cube[i]->LoadModel(L"cmo/Grassy.cmo");
			}
			else if (y >= 0)
			{
				m_cube[i]->LoadModel(L"cmo/Sand.cmo");
			}
			else if (y >= -3)
			{
				m_cube[i]->LoadModel(L"cmo/Water.cmo");
			}
			else if (y >= -6)
			{
				m_cube[i]->LoadModel(L"cmo/Stone.cmo");
			}

			m_cube[i]->SetTranslation(pos);
		}
		else
		{
			if (y >= 2)
			{
				color = Vector4(Colors::Green);
			}
			else if (y >= 0)
			{
				color = Vector4(Colors::SaddleBrown);
			}
			else if (y >= -3)
			{
				color = Vector4(Colors::RoyalBlue);
			}
			else if (y >= -6)
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
		for (std::vector<std::unique_ptr<Obj3d>>::iterator it = m_cube.begin();
			it != m_cube.end();
			it++)
		{
			(*it)->Update();
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
		for (std::vector<std::unique_ptr<Obj3d>>::iterator it = m_cube.begin();
			it != m_cube.end();
			it++)
		{
			(*it)->Draw();
		}
	}

}

void RandomMapMaker::Finalize()
{
	for (std::vector<std::unique_ptr<VertexCube>>::iterator it = m_VertexCube.begin();
		it != m_VertexCube.end();
		it++)
	{
		(*it).reset();
	}

	for (std::vector<std::unique_ptr<Obj3d>>::iterator it = m_cube.begin();
		it != m_cube.end();
		it++)
	{
		(*it).reset();
	}
}


//


#include <random>
#include <ctime>
#include <d3d11.h>

#include "DXTKGroup.h"
#include "RandomMapMaker.h"
#include "MemoryLeakDetector.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;



RandomMapMaker::RandomMapMaker()
{
	srand((unsigned int)time(NULL));

	seedX = 0;
	seedZ = 0;

	width = 40;
	depth = 40;

	MaxHeight = 10;

	relief = 15.0f;

	m_cube.resize(width * depth);

	SetUpMemoryLeakDetector();

	Initialize();
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//������
//
//
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void RandomMapMaker::Initialize()
{
	seedX = rand() % 100;
	seedZ = rand() % 100;

	m_VertexCube.resize(width * depth);
	for (int j = 0; j < width * depth; j++)
	{
		Matrix world;

		//�@�X�P�[�����O�s��
		Matrix scalemat = Matrix::CreateScale(Vector3(1, 1, 1));

		Vector3 pos = Vector3(j / width, MakeY(j / width,j % depth), j % depth);

		//�@���s�ړ��s��
		Matrix transmat = Matrix::CreateTranslation(pos);

		//�@���[���h�s�������
		world = scalemat * transmat;

		XMVECTOR color;

		if (MakeY(j / width, j % depth) >= 2)
		{
			color = Colors::Green;		
		}
		else if (MakeY(j / width, j % depth) >= 0)
		{
			color = Colors::SaddleBrown;
		}
		else if (MakeY(j / width, j % depth) >= -3)
		{
			color = Colors::RoyalBlue;
		}
		else if (MakeY(j / width, j % depth) >= -6)
		{
			color = Colors::Gray;
		}
		m_VertexCube[j] = std::make_unique<VertexCube>(world, color);
	}
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//�X�V����
//
//
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void RandomMapMaker::Update()
{
	for (std::vector<std::unique_ptr<VertexCube>>::iterator it = m_VertexCube.begin();
		it != m_VertexCube.end();
		it++)
	{
		(*it)->Update();
	}

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
	for (std::vector<std::unique_ptr<VertexCube>>::iterator it = m_VertexCube.begin();
		it != m_VertexCube.end();
		it++)
	{
		(*it)->Render();
	}
}


//

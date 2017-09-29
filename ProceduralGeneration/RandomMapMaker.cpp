
#include <random>
#include <ctime>
#include <d3d11.h>

#include "DXTKGroup.h"
#include "RandomMapMaker.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;


using Microsoft::WRL::ComPtr;
using VT = VertexPositionNormalColor;		//���̓��C�A�E�g���ʒu�A�F
using PB = PrimitiveBatch<VT>;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//�@�ÓI�����o�̎���
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

//�@�J����
Camera*								    RandomMapMaker::m_pCamera;



// �����̂̒��_�f�[�^
VertexPositionNormalColor vertexes_n[] =
{
	// ����
	{ Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Red },
	{ Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Yellow },
	{ Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Green },
	{ Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Blue },

	// �E��													  			    
	{ Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::Black },
	{ Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::White },

	// ����													  			    
	{ Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Purple },
	{ Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Pink },
};


//�@���_�C���f�b�N�X
uint16_t indexes[] =
{
	2,1,0,	//�@�\
	3,1,2,	//�@�\
	4,3,2,	//�@�E
	5,3,4,	//�@�E
	0,7,6,	//�@��
	1,7,0,	//�@��
	6,7,4,	//�@��
	4,7,5,	//�@��
	4,0,6,	//�@��
	2,0,4,	//�@��
	7,1,5,	//�@��
	5,1,3,	//�@��
};


void RandomMapMaker::InitializeStatic(Camera * pCamera)
{
	m_pCamera = pCamera;
}

RandomMapMaker::RandomMapMaker()
{
	srand((unsigned int)time(NULL));

	seedX = 0;
	seedZ = 0;

	width = 30;
	depth = 30;

	MaxHeight = 10;

	relief = 15.0f;

	m_cube.resize(width * depth);

	PolygonInit();

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

	//�@�L���[�u����
	for (int i = 0; i < width*depth; i++)
	{
		Vector3 pos = Vector3(i / width, 0, i % depth);

		//�L���[�u�쐬
		m_cube[i].SetTranslation(pos);
		MakeY(i);

		if (m_cube[i].GetTranslation().y >= 2)
		{
			m_cube[i].LoadModel(L"cmo/Grassy.cmo");
		}
		else if (m_cube[i].GetTranslation().y >= 0)
		{
			m_cube[i].LoadModel(L"cmo/Sand.cmo");
		}
		else if (m_cube[i].GetTranslation().y >= -3)
		{
			m_cube[i].LoadModel(L"cmo/Water.cmo");
		}
		else if (m_cube[i].GetTranslation().y >= -5)
		{
			m_cube[i].LoadModel(L"cmo/Stone.cmo");
		}
		
	}
}

//
void RandomMapMaker::PolygonInit()
{
	// DirectXTK�̊Ǘ��I�u�W�F�N�g�̏�����
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	//�v���~�e�B�u�o�b�`���쐬
	primitiveBatch = std::make_unique<PB>(dxtk.m_context);

	//�G�t�F�N�g���쐬
	basicEffect = std::make_unique<BasicEffect>(dxtk.m_device);

	basicEffect->SetVertexColorEnabled(true);

	basicEffect->SetAmbientLightColor(Vector3(0.5f, 0.5f, 1.0f));

	basicEffect->SetLightDiffuseColor(0, Vector3(0.2f, 1.0f, 0.2f));

	basicEffect->SetLightEnabled(0, true);

	basicEffect->SetLightDiffuseColor(0, Vector3(0.2f, 1.0f, 0.2f));

	basicEffect->SetLightDirection(0, Vector3(1.0f, -0.5f, 2.0f));

	basicEffect->SetLightEnabled(1, true);

	basicEffect->SetLightDiffuseColor(1, Vector3(0.5f, 0.2f, 0.3f));

	basicEffect->SetLightDirection(1, Vector3(-1.0f, -0.5f, -2.0f));

	////���_�F���g�p����̂��G�t�F�N�g�ɋ�����
	//basicEffect->SetVertexColorEnabled(false);	// ���_�J���[(OFF)
	//basicEffect->SetLightingEnabled(false);		// ���C�g(ON)
	//basicEffect->SetTextureEnabled(true);		// �e�N�X�`��(OFF)
	//basicEffect->SetPerPixelLighting(false);	// �s�N�Z�����C�e�B���O(OFF)

	//���̓��C�A�E�g���쐬����
	//����g�p���钸�_�V�F�[�_�[����������
	void const* shaderByteCode;	// �v���O�����̐擪�A�h���X

	size_t byteCodeLength;		// �v���O�����̃T�C�Y

	basicEffect->GetVertexShaderBytecode(
		&shaderByteCode, &byteCodeLength);


	dxtk.m_device->CreateInputLayout(
		VertexPositionNormalColor::InputElements,
		VertexPositionNormalColor::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		inputLayout.GetAddressOf());
}



//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//�X�V����
//
//
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void RandomMapMaker::Update()
{
	m_pCamera->Update();
	m_view = m_pCamera->GetViewMatrix();
	m_proj = m_pCamera->GetProjectionMatrix();
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
	//RandomHeighit = rand() % MaxHeight;
	//Vector3 localPos = Vector3(m_cube[number].GetTranslation().x, y, m_cube[number].GetTranslation().z);*/
	//m_cube[number].SetTranslation(localPos);

	

	float xSample = (m_cube[number].GetTranslation().x + seedX) / relief;
	float zSample = (m_cube[number].GetTranslation().z + seedZ) / relief;

	float noise = m_noise.noise(xSample, zSample);

	y = MaxHeight * noise;
	Vector3 localPos = Vector3(m_cube[number].GetTranslation().x, y, m_cube[number].GetTranslation().z);
	m_cube[number].SetTranslation(localPos);
}


//
//
//
//
void RandomMapMaker::Draw()
{
	PolygonDraw();

	// �S�����`��
	for (int i = 0; i < width * depth; i++)
	{
		//m_cube[i].Draw();
	}
}


//
void RandomMapMaker::PolygonDraw()
{
	// DirectXTK�̊Ǘ��I�u�W�F�N�g�̏�����
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	// ���[���h�s��A�r���[�s��A�ˉe�s���ݒ�
	basicEffect->SetWorld(m_world);
	basicEffect->SetView(m_view);
	basicEffect->SetProjection(m_proj);
	basicEffect->Apply(dxtk.m_context);

	// �[�x�E�X�e���V���̐ݒ�i�ʏ�̐ݒ�j
	dxtk.m_context->OMSetDepthStencilState(
		dxtk.m_state->DepthDefault(), 0);

	// �u�����h�X�e�[�g�̐ݒ�i�s�����j
	dxtk.m_context->OMSetBlendState(
		dxtk.m_state->Opaque(), nullptr, 0XFFFFFFFF);

	// �J�����O�̐ݒ�i�J�����O�͂��Ȃ��j
	dxtk.m_context->RSSetState(dxtk.m_state->CullCounterClockwise());

	dxtk.m_context->IASetInputLayout(inputLayout.Get());

	// �v���~�e�B�u�̕`��
	primitiveBatch->Begin();

	// �O�p�`���X�g�̕`��
	primitiveBatch->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indexes, 6 * 6, vertexes_n, 4 * 6);

	primitiveBatch->End();
}
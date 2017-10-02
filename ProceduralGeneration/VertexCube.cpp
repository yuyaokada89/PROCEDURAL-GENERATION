#include <d3d11.h>

#include "VertexCube.h"
#include "DXTKGroup.h"
#include "MemoryLeakDetector.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;
using VT = VertexPositionNormalColor;		//���̓��C�A�E�g���ʒu�A�F
using PB = PrimitiveBatch<VT>;


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//�@�ÓI�����o�̎���
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

//�@�J����
Camera*								    VertexCube::m_pCamera;



void VertexCube::InitializeStatic(Camera * pCamera)
{
	m_pCamera = pCamera;
}

VertexCube::VertexCube(Matrix world,XMVECTOR color)
{
	m_world = world;

	m_color = color;

	VertexColorCreate();

	SetUpMemoryLeakDetector();

	PolygonInit();
}

void VertexCube::VertexColorCreate()
{
	vex[0] =
	{
		Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f),m_color 	//0
	};
	vex[1] =
	{
		Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f),m_color 	//1
	};
	vex[2] =
	{
		Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f) ,m_color 	//2
	};
	vex[3] =
	{
		Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,m_color 	//3
	};
	vex[4] =
	{
		Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,m_color 	//4
	};
	vex[5] =
	{
		Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,m_color 	//5
	};
	vex[6] =
	{
		Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,m_color 	//6
	};
	vex[7] =
	{
		Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,m_color 	//7
	};
}

void VertexCube::PolygonInit()
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


void VertexCube::Update()
{
	m_pCamera->Update();
	m_view = m_pCamera->GetViewMatrix();
	m_proj = m_pCamera->GetProjectionMatrix();
}

void VertexCube::Render()
{
	PolygonDraw();
}


void VertexCube::PolygonDraw()
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
		m_indexes, 6 * 6, vex, 4 * 6);
	primitiveBatch->End();
	
}
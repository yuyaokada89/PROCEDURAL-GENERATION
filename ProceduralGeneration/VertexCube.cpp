#include <d3d11.h>

#include "VertexCube.h"
#include "DXTKGroup.h"

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


// �����̂̒��_�f�[�^
VertexPositionNormalColor vertexes_g[] =
{
	// ����
	{ Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//0
	{ Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//1
	{ Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//2
	{ Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//3

	// �E��													  			    
	{ Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::LightGreen },	//4
	{ Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::LightGreen },	//5

	// ����													  			    
	{ Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//6
	{ Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//7
};

// �����̂̒��_�f�[�^
VertexPositionNormalColor vertexes_st[] =
{
	// ����
	{ Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//0
	{ Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//1
	{ Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//2
	{ Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//3

																					// �E��													  			    
	{ Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::Silver },	//4
	{ Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::Silver },	//5

																					// ����													  			    
	{ Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//6
	{ Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//7
};

// �����̂̒��_�f�[�^
VertexPositionNormalColor vertexes_w[] =
{
	// ����
	{ Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//0
	{ Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//1
	{ Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//2
	{ Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//3

																					// �E��													  			    
	{ Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::LightSkyBlue },	//4
	{ Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::LightSkyBlue },	//5

																					// ����													  			    
	{ Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//6
	{ Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//7
};


// �����̂̒��_�f�[�^
VertexPositionNormalColor vertexes_sa[] =
{
	// ����
	{ Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//0
	{ Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//1
	{ Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//2
	{ Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//3

																						// �E��													  			    
	{ Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::Brown },	//4
	{ Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::Brown },	//5

																					// ����													  			    
	{ Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//6
	{ Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//7
};

//�@���_�C���f�b�N�X
uint16_t indexes_g[] =
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

//�@���_�C���f�b�N�X
uint16_t indexes_sa[] =
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

//�@���_�C���f�b�N�X
uint16_t indexes_w[] =
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

//�@���_�C���f�b�N�X
uint16_t indexes_st[] =
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


void VertexCube::InitializeStatic(Camera * pCamera)
{
	m_pCamera = pCamera;
}

VertexCube::VertexCube(Matrix world,int Height_num)
{
	m_world = world;
	m_height_num = Height_num;

	PolygonInit();
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

	switch (m_height_num)
	{
	case 0:
		// �v���~�e�B�u�̕`��
		primitiveBatch->Begin();
		// �O�p�`���X�g�̕`��
		primitiveBatch->DrawIndexed(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			indexes_g, 6 * 6, vertexes_g, 4 * 6);
		primitiveBatch->End();
		break;
	case 1:
		// �v���~�e�B�u�̕`��
		primitiveBatch->Begin();
		// �O�p�`���X�g�̕`��
		primitiveBatch->DrawIndexed(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			indexes_sa, 6 * 6, vertexes_sa, 4 * 6);
		primitiveBatch->End();
		break;
	case 2:
		// �v���~�e�B�u�̕`��
		primitiveBatch->Begin();
		// �O�p�`���X�g�̕`��
		primitiveBatch->DrawIndexed(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			indexes_w, 6 * 6, vertexes_w, 4 * 6);
		primitiveBatch->End();
		break;
	case 3:
		// �v���~�e�B�u�̕`��
		primitiveBatch->Begin();
		// �O�p�`���X�g�̕`��
		primitiveBatch->DrawIndexed(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			indexes_st, 6 * 6, vertexes_st, 4 * 6);
		primitiveBatch->End();
		break;
	}

	

	
}
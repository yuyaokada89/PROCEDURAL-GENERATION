#include "../pch.h"
#include "SceneManager.h"
#include "VertexRender.h"
#include "FBXRender.h"
#include "../DXTKGroup.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;

SceneBase* VertexRender::m_base = NULL;

SceneBase* VertexRender::GetInstance()
{
	//if (m_base == NULL)
	//{
		m_base = new VertexRender();
	//}
	return m_base;
}

VertexRender::VertexRender()
{
	m_outputWidth = 800;
	m_outputHeight = 600;
	this->Initialize();
}

VertexRender::~VertexRender()
{
}

void VertexRender::Initialize()
{
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();


	std::make_unique<SpriteBatch>(dxtk.m_context);
	std::make_unique<SpriteFont>(dxtk.m_device, L"myfile.spritefont");

	//�@�J�����̐���
	m_camera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);

	//�@3D�I�u�W�F�N�g�N���X�̐ÓI�����o��������
	Obj3d::InitializeStatic(
		m_camera.get()
		, dxtk.m_device
		, dxtk.m_context
	);

	VertexCube::InitializeStatic(m_camera.get());

	m_angle = 0;

	m_map = std::make_unique<RandomMapMaker>();

	m_map->SetFlag(false);

}

void VertexRender::UpdateScene(SceneManager* scene)
{
	/*DirectX���Ǘ�����I�u�W�F�N�g���擾����*/
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();	
	auto kb = dxtk.m_keyboard->GetState();
	// �L�[���͂̍X�V
	dxtk.UpdateInputState();

	//�@�J�����̍X�V
	m_camera->Update();
	m_view = m_camera->GetViewMatrix();
	m_proj = m_camera->GetProjectionMatrix();

	//�@�J�����㏸
	if (kb.IsKeyDown(Keyboard::Keys::Up))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(0, 0.1f, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	// �J�������~
	if (kb.IsKeyDown(Keyboard::Keys::Down))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(0, -0.1f, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//�@�J�����E�ړ�
	if (kb.IsKeyDown(Keyboard::Keys::Right))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(0.1f, 0, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//�@�J�������ړ�
	if (kb.IsKeyDown(Keyboard::Keys::Left))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(-0.1f, 0, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//�@�J�����O�i
	if (kb.IsKeyDown(Keyboard::Keys::W))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(0, 0, -0.1f);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//�@�J�������
	if (kb.IsKeyDown(Keyboard::Keys::S))
	{
		// ���݂̍��W�E��]�p���擾
		Vector3 trans = m_camera->GetTranslation();
		// �ړ��x�N�g��(Z���W���)
		Vector3 moveV(0, 0, 0.1f);
		Matrix rotm = Matrix::CreateRotationY(0);
		// �ړ��x�N�g������]����
		moveV = Vector3::TransformNormal(moveV, rotm);
		// �ړ�
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	const float rotSpeed = 0.5f;

	//�@�J�������
	if (kb.IsKeyDown(Keyboard::Keys::Q))
	{
		m_angle -= rotSpeed;
		m_camera->SetTargetAngle(XMConvertToRadians(m_angle));
	}

	//�@�J�������
	if (kb.IsKeyDown(Keyboard::Keys::P))
	{
		m_angle += rotSpeed;
		m_camera->SetTargetAngle(XMConvertToRadians(m_angle));
	}

	m_map->Update();

	/*if (kb.IsKeyDown(Keyboard::Keys::Escape))
	{
		ExitGame();
	}*/


	if (dxtk.m_keyTracker->IsKeyPressed(Keyboard::Keys::F))
	{
		VertexRender tScene;
		tScene.Initialize();

		scene->Scene(FBXRender::GetInstance());

		Dispose();
	}

}

void VertexRender::RenderScene()
{
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	m_map->Draw();

	dxtk.m_spriteBatch->Begin();
	dxtk.m_spriteFont->DrawString(dxtk.m_spriteBatch.get(), L"VertexRender", XMFLOAT2(100, 100));
	dxtk.m_spriteBatch->End();
}

void VertexRender::Dispose()
{
	if (m_base != NULL)
	{
		delete m_base;
	}
}
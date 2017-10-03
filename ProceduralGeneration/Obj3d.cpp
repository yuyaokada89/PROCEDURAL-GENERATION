//
//�@3D�I�u�W�F�N�g�̃N���X
//

//�@�w�b�_�t�@�C���̃C���N���[�h
#include "Obj3d.h"
#include "DXTKGroup.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//�@�ÓI�����o�̎���
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

//�@�J����
Camera*								    Obj3d::m_pCamera;

/*�ėp�`��X�e�[�g*/
std::unique_ptr<DirectX::CommonStates>  Obj3d::m_states;

//�G�t�F�N�g�t�@�N�g��
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;


//�@�R���X�g���N�^
Obj3d::Obj3d()
{
	//�@�ϐ��̏�����
	m_scale = Vector3(1, 1, 1);

	//�@�f�t�H���g�ł̓N�H�[�^�j�I�����g��Ȃ�
	m_UseQuternion = false;
}

Obj3d::~Obj3d()
{
}



void Obj3d::InitializeStatic(Camera * pCamera, 
	Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, 
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext)
{
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	m_pCamera = pCamera;

	m_states = std::make_unique<CommonStates>(dxtk.m_device);
	m_factory = std::make_unique<EffectFactory>(dxtk.m_device);
	m_factory->SetDirectory(L"Resources");
}


void Obj3d::LoadModel(const wchar_t *filename)
{
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	/*���f���̓ǂݍ���*/
	m_model = Model::CreateFromCMO(dxtk.m_device, filename, *m_factory);
}

void Obj3d::Update()
{
	//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	// �s����v�Z����
	//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
	 
	//�@�X�P�[�����O�s��
	Matrix scalemat = Matrix::CreateScale(m_scale);
	
	//�@��]�s��
	Matrix rotmat;

	//�@��]�s��
	if (m_UseQuternion)
	{//�@�N�H�[�^�j�I�������]�s����v�Z����
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{//�@�I�C���[�p�����]�s����v�Z����
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);

		rotmat = rotmatZ * rotmatX * rotmatY;
	}
	//�@���s�ړ��s��
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//�@���[���h�s�������
	m_world = scalemat * rotmat * transmat;
	
}

void Obj3d::Draw()
{
	//�@���f�������݂��Ă���Ε`��
	if (m_model != nullptr)
	{

		DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

			m_model->Draw(dxtk.m_context,
				*m_states,
				m_world,
				m_pCamera->GetViewMatrix(),
				m_pCamera->GetProjectionMatrix());
	}
}

void Obj3d::Finalize()
{
	m_states.reset();
	m_factory.reset();
	m_model.reset();
}
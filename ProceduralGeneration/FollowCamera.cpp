//
//
//


//�@�w�b�_�t�@�C���̃C���N���[�h
#include "FollowCamera.h"

using namespace DirectX;
using namespace SimpleMath;

//�@�ÓI�����o�ϐ��̏�����
const float CAMERA_DISTANCE = 5.0f;

FollowCamera::FollowCamera(int windowWidth, int windowHeight)
	:Camera(windowWidth, windowHeight)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0f;
	m_keyboard = nullptr;
	m_isFPS = false;
	InitializeTPS();
}

void FollowCamera::SetTargetPos(const Vector3 &targetPos)
{
	m_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(const float targetAngle)
{
	m_targetAngle = targetAngle;
}

// �J�����ݒ�@���^���N�̈ړ���������ōs��
void FollowCamera::Update()
{
	 //�@�J��������
	const float CAMERA_DISTANCE = 5.0f;
	//�@���_�A�Q�Ɠ_
	Vector3 eyepos, refpos;

	//�@�L�[�{�[�h�̎擾
	Keyboard::State keystate = m_keyboard->GetState();
	m_keyboardTracker.Update(keystate);

	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keyboard::C))
	{
		// �t���O��؂�ւ���
		m_isFPS = !m_isFPS;
		if (!m_isFPS)
		{
			InitializeTPS();
		}
	}

	if (m_isFPS == true)
	{//FPS�J����
		Vector3 position;
		//�@���@�̏��0.2m�̈ʒu�ɃJ������u��
		position = m_targetPos + Vector3(0, 1.6f, 0);
		//�@�Q�Ɠ_���王�_�ւ̍���
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);
		//�@���@�̌��ɉ�荞�ނ��߂̉�]
		Matrix rotCamera = Matrix::CreateRotationY(m_targetAngle);
		//�@�����x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotCamera);
		eyepos = position + cameraV * 0.1f;
		//�@�Q�Ɠ_���W���v�Z
		refpos = eyepos + cameraV;
	}

	if (m_isFPS == false)
	{//TPS�J����
		//�@�^�[�Q�b�g�̍��W�́A���@�̍��W�ɒǏ]
		refpos = m_targetPos + Vector3(0, 2.0f, 0);
		//�@�^�[�Q�b�g���W����J�������W�ւ̍���
		Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);


		//�@�J�����̎��������̋t�����ɉ�]
		Matrix rotCamera = Matrix::CreateRotationY(m_targetAngle);
		cameraV = Vector3::TransformNormal(cameraV, rotCamera);

		//�@�J�������W���v�Z
		eyepos = refpos + cameraV;

		eyepos = m_eyePos + (eyepos - m_eyePos)*0.05;
		refpos = m_refPos + (refpos - m_refPos)*0.05;
	}

	

	// �J�����ɏ��𑗂�
	SetEyePos(eyepos);
	SetRefPos(refpos);
	//�@�J�����̍X�V
	Camera::Update();
}

void FollowCamera::SetKeyboard(DirectX::Keyboard *keyboard)
{
	m_keyboard = keyboard;
}

void FollowCamera::InitializeTPS()
{
	//�@�J��������
	const float CAMERA_DISTANCE = 5.0f;
	Vector3 eyepos, refpos;

	//�@�^�[�Q�b�g�̍��W�́A���@�̍��W�ɒǏ]
	refpos = m_targetPos + Vector3(0, 2.0f, 0);
	//�@�^�[�Q�b�g���W����J�������W�ւ̍���
	Vector3 cameraV(0.0f, 0.0f, CAMERA_DISTANCE);


	//�@�J�����̎��������̋t�����ɉ�]
	Matrix rotCamera = Matrix::CreateRotationY(m_targetAngle);
	cameraV = Vector3::TransformNormal(cameraV, rotCamera);

	//�@�J�������W���v�Z
	eyepos = refpos + cameraV;

	// �J�����ɏ��𑗂�
	SetEyePos(eyepos);
	SetRefPos(refpos);
}
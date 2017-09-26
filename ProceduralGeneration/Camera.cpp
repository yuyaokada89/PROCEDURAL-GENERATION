
#include "Camera.h"

using namespace DirectX;
using namespace SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="windowWidth","windowHeight">�E�B���h�E�̉����Əc��</param>
/// <returns>�Ȃ�</returns>

Camera::Camera(int windowWidth,int windowHeight)
{
	//�@�����o�ϐ��̏�����
	m_eyePos = Vector3(0.0f, 0.0f, 5.0f);
	m_refPos = Vector3(0.0f, 0.0f, 0.0f);
	m_upVec = Vector3(0.0f, 1.0f, 0.0f);
	m_upVec.Normalize();

	m_fovY = XMConvertToRadians(60.0f);
	m_aspect = (float)windowWidth / windowHeight;
	m_nearclip = 0.1f;
	m_farclip = 1000.0f;

	//�@�r���[�s��𐶐�
	m_viewMatrix = Matrix::Identity;
	//�@�ˉe�s��𐶐�
	m_projMatrix = Matrix::Identity;
}

Camera::~Camera()
{

}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="">�Ȃ�</param>
/// <returns>�Ȃ�</returns>
/// 
void Camera::Update()
{
	//�@�r���[�s��𐶐�
	m_viewMatrix = Matrix::CreateLookAt(m_eyePos, m_refPos, m_upVec);

	//�@�ˉe�s��𐶐�
	m_projMatrix = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}

Matrix Camera::GetViewMatrix()
{
	return m_viewMatrix;
}


Matrix Camera::GetProjectionMatrix()
{
	return m_projMatrix;
}

void Camera::SetEyePos(Vector3 &eyePos)
{
	m_eyePos = eyePos;
}

void Camera::SetRefPos(Vector3 &refPos)
{
	m_refPos = refPos;
}

void Camera::SetUpVec(Vector3 &upVec)
{
	m_upVec = upVec;
}

void Camera::SetFovY(float fovY)
{
	m_fovY = fovY;
}

void Camera::SetAspect(int windowWidth,int windowHeight)
{
	m_aspect = (float)windowWidth / windowHeight;
}

void Camera::SetNearClip(float nearclip)
{
	m_nearclip = nearclip;
}

void Camera::SetFarClip(float farclip)
{
	m_farclip = farclip;
}
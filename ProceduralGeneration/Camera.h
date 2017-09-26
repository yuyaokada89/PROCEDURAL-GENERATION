//�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//�@�J�����𐧌䂷��N���X
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\

//�@���d�C���N���[�h�̖h�~
#pragma once

//�@�w�b�_�t�@�C���̃C���N���[�h
#include <d3d11.h>
#include <SimpleMath.h>


class Camera
{
	public:
		//�@�����o�֐���u���Ƃ���
		Camera(int windowWidth,int windowHeight);

		virtual ~Camera();

		//�@�X�V
		virtual void Update();

		// �r���[���W���擾
		DirectX::SimpleMath::Matrix GetViewMatrix();

		//�@�ˉe�s����擾
		DirectX::SimpleMath::Matrix GetProjectionMatrix();

		//�@���_���W���Z�b�g
		void SetEyePos(DirectX::SimpleMath::Vector3 &eyepos);
		//�@�����_���W���Z�b�g
		void SetRefPos(DirectX::SimpleMath::Vector3 &refpos);
		//�@������x�N�g�����Z�b�g
		void SetUpVec(DirectX::SimpleMath::Vector3 &upVec);
		//�@������������p���Z�b�g
		void SetFovY(float fovY);
		//�@�A�X�y�N�g����Z�b�g
		void SetAspect(int windowWidth,int windowHeight);
		//�@��O�̌��E�������Z�b�g
		void SetNearClip(float nearclip);
		//�@���̌��E�������Z�b�g
		void SetFarClip(float farclip);

	protected:
		//�@�����o�ϐ���u���Ƃ���

		//�@�r���[�s��
		DirectX::SimpleMath::Matrix m_viewMatrix;
		//�@���_���W
		DirectX::SimpleMath::Vector3 m_eyePos;
		//�@�����_���W
		DirectX::SimpleMath::Vector3 m_refPos;
		//�@������x�N�g��
		DirectX::SimpleMath::Vector3 m_upVec;


		//�@�ˉe�s��
		DirectX::SimpleMath::Matrix m_projMatrix;
		//�@������������p
		float m_fovY;
		//�@��ʉ����Əc���̔䗦�i�A�X�y�N�g��j
		float m_aspect;
		//�@��O�̌��E����
		float m_nearclip;
		//�@���̌��E����
		float m_farclip;
};

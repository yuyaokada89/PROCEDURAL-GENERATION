//
//�@���@�ɒǏ]����J�����N���X
//


//�@���d�C���N���[�h�̖h�~
#pragma once

//�@�w�b�_�t�@�C���̃C���N���[�h
#include "Camera.h"
#include <Keyboard.h>

class FollowCamera :public Camera
{
	public:
		//�@�J�����Ǝ��@�̍��W
		static const float CAMERA_DISTANCE;
		//�@�R���X�g���N�^
		FollowCamera(int windowWidth, int windowHeight);
		//�@�Ǐ]�Ώۍ��W���Z�b�g
		void SetTargetPos(const DirectX::SimpleMath::Vector3 &targetpos);
		//�@�Ǐ]�Ώۊp�x���Z�b�g
		void SetTargetAngle(const float angle);
		//�@���t���[���X�V
		void Update()override;
		//�@TPS�J�����̏�����
		void InitializeTPS();
		//�@���s�ړ����擾
		const DirectX::SimpleMath::Vector3& GetTranslation() { return m_targetPos; }

	protected:
		//�@�Ǐ]�Ώۂ̍��W
		DirectX::SimpleMath::Vector3 m_targetPos;
		//�@�Ǐ]�Ώۂ̍��W
		float m_targetAngle;
		//�@�J�����t���O
		bool m_isFPS;
};


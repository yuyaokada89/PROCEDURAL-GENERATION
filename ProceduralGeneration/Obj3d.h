//
//�@�R�c�I�u�W�F�N�g�̃N���X
//

//�@���d�C���N���[�h�̖h�~
#pragma once

//�@�w�b�_�t�@�C���̃C���N���[�h
#include <windows.h>
#include <wrl/client.h>
#include <memory>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include "Camera.h"

class Obj3d
{
	//�@�ÓI�����o
	public:
		static void InitializeStatic(Camera* pCamera
			,Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice
			,Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext);

	private:
		//�@�J����
		static Camera*											m_pCamera;
		//�@�ėp�X�e�[�g
		static std::unique_ptr<DirectX::CommonStates>			m_states;
		//�@�f�o�C�X
		static Microsoft::WRL::ComPtr<ID3D11Device>				m_d3dDevice;
		//�@�R���e�L�X�g
		static Microsoft::WRL::ComPtr<ID3D11DeviceContext>		m_d3dContext;
		//�@�G�t�F�N�g�t�@�N�g��
		static std::unique_ptr<DirectX::EffectFactory>			m_factory;

	public:
		//�@�R���X�g���N�^
		Obj3d();

		//�@���f���̓ǂݍ���
		void LoadModel(const wchar_t *filename);

		//�@�X�V����
		void Update();

		//�@�`�揈��
		void Draw();

		//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
		//�@setter
		//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\

		//�@�X�P�[�����O�p
		void SetScale(const DirectX::SimpleMath::Vector3 &scale) { m_scale = scale; }
		//�@��]�p�p
		void SetRotation(const DirectX::SimpleMath::Vector3 &rotation) { m_rotation = rotation; m_UseQuternion = false; }
		//�@��]�p�p�i�N�H�[�^�[�j�I���p�j
		void SetRotationQ(const DirectX::SimpleMath::Quaternion &rotationQ) { m_rotationQ = rotationQ; m_UseQuternion = true; }
		//�@���s�ړ��p
		void SetTranslation(const DirectX::SimpleMath::Vector3 &translation) { m_translation = translation; }
		//�@���[�J�����[���h
		void SetWorld(const DirectX::SimpleMath::Matrix &world) { m_world = world; }
		//�@�e�s��p
		void SetObjectParent(Obj3d *pObjParent) { m_pObjParent = pObjParent; }
		//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
		//�@getter
		//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
		
		//�@�X�P�[�����O���擾
		const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
		//�@��]���擾
		const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
		//�@���s�ړ����擾
		const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }
		//�@���[���h�s����擾
		const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }
		//�@�e�s����擾
		Obj3d* GetObjParent() { return m_pObjParent; }
		
	private:
		//�@���f���̃��j�[�N�|�C���^
		std::unique_ptr<DirectX::Model>	m_model;
		//�@�X�P�[�����O
		DirectX::SimpleMath::Vector3	m_scale;
		//�@��]�p�i�I�C���[�p�j
		DirectX::SimpleMath::Vector3	m_rotation;
		//�@��]�p�i�N�H�[�^�j�I���j
		DirectX::SimpleMath::Quaternion m_rotationQ;
		//�@���s�ړ�
		DirectX::SimpleMath::Vector3	m_translation;
		//�@���[���h�s��
		DirectX::SimpleMath::Matrix		m_world;
		//�@�e�ƂȂ�R�c�I�u�W�F�N�g�̃N���X�̃|�C���^
		Obj3d* m_pObjParent;
		//�@��]���N�H�[�^�j�I���Ŏ����Ă���t���O
		bool m_UseQuternion;
};
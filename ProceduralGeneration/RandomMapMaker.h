#include "Obj3d.h"
#include "PerlinNoise.hpp"
#include "FollowCamera.h"

#include <vector>
#include <VertexTypes.h>
#include <PrimitiveBatch.h>

#pragma once


class RandomMapMaker
{
public:
	static void InitializeStatic(Camera* pCamera);

private:
	//�@�J����
	static Camera*											m_pCamera;

	//�@�V�[�h�l
	float seedX;
	float seedZ;

	//�@�}�b�v�̃T�C�Y
	int width;
	int depth;


	//�@�����̍ő�l
	int MaxHeight;

	int RandomHeighit;

	int y;

	//�@�N���̌�����
	float relief;

	//�@���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	// �����f��
	std::vector<Obj3d>	m_cube;

	siv::PerlinNoise m_noise;

	//�v���~�e�B�u��\�����邽�߂Ɏg��
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormalColor>>primitiveBatch;

	//�G�t�F�N�g�i�V�F�[�_�[�֌W���܂Ƃ߂��N���X�j
	std::unique_ptr<DirectX::BasicEffect>basicEffect;


	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

public:
	//�@������
	RandomMapMaker();

	void MakeY(int number);

	// ������
	void Initialize();

	//�@�X�V����
	void Update();

	//�@�s��X�V
	void Calc();

	//�@�`��
	void Draw();

	void PolygonInit();

	void PolygonDraw();
};

#include <VertexTypes.h>
#include <PrimitiveBatch.h>
#include <Effects.h>
#include <wrl/client.h>

#include "Camera.h"

#pragma once

class VertexCube
{
public:
	static void InitializeStatic(Camera* pCamera);

private:
	//�@�J����
	static Camera*											m_pCamera;

	//�@���[���h�s��
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//�v���~�e�B�u��\�����邽�߂Ɏg��
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormalColor>>primitiveBatch;

	//�G�t�F�N�g�i�V�F�[�_�[�֌W���܂Ƃ߂��N���X�j
	std::unique_ptr<DirectX::BasicEffect>basicEffect;

	//�C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

	int m_height_num;

	DirectX::VertexPositionNormalColor vex[8];

	DirectX::XMVECTOR m_color;

	uint16_t m_indexes[36] =
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

public:

	VertexCube(DirectX::SimpleMath::Matrix world,DirectX::XMVECTOR color);

	void VertexColorCreate();

	void Update();

	void Render();

	void PolygonInit();

	void PolygonDraw();

};
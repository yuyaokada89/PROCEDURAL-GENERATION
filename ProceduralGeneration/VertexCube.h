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

public:

	VertexCube(DirectX::SimpleMath::Matrix world);

	void Update();

	void Render();

	void PolygonInit();

	void PolygonDraw();

};
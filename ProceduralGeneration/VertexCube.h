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
	//　カメラ
	static Camera*											m_pCamera;

	//　ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//プリミティブを表示するために使う
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormalColor>>primitiveBatch;

	//エフェクト（シェーダー関係をまとめたクラス）
	std::unique_ptr<DirectX::BasicEffect>basicEffect;

	//インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

public:

	VertexCube(DirectX::SimpleMath::Matrix world);

	void Update();

	void Render();

	void PolygonInit();

	void PolygonDraw();

};
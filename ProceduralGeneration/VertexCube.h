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

	int m_height_num;

	DirectX::VertexPositionNormalColor vex[8];

	DirectX::XMVECTOR m_color;

	uint16_t m_indexes[36] =
	{
		2,1,0,	//　表
		3,1,2,	//　表
		4,3,2,	//　右
		5,3,4,	//　右
		0,7,6,	//　左
		1,7,0,	//　左
		6,7,4,	//　裏
		4,7,5,	//　裏
		4,0,6,	//　上
		2,0,4,	//　上
		7,1,5,	//　下
		5,1,3,	//　下
	};

public:

	VertexCube(DirectX::SimpleMath::Matrix world,DirectX::XMVECTOR color);

	void VertexColorCreate();

	void Update();

	void Render();

	void PolygonInit();

	void PolygonDraw();

};
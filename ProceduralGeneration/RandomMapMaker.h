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
	//　カメラ
	static Camera*											m_pCamera;

	//　シード値
	float seedX;
	float seedZ;

	//　マップのサイズ
	int width;
	int depth;


	//　高さの最大値
	int MaxHeight;

	int RandomHeighit;

	int y;

	//　起伏の激しさ
	float relief;

	//　ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	// 箱モデル
	std::vector<Obj3d>	m_cube;

	siv::PerlinNoise m_noise;

	//プリミティブを表示するために使う
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormalColor>>primitiveBatch;

	//エフェクト（シェーダー関係をまとめたクラス）
	std::unique_ptr<DirectX::BasicEffect>basicEffect;


	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;

public:
	//　初期化
	RandomMapMaker();

	void MakeY(int number);

	// 初期化
	void Initialize();

	//　更新処理
	void Update();

	//　行列更新
	void Calc();

	//　描画
	void Draw();

	void PolygonInit();

	void PolygonDraw();
};

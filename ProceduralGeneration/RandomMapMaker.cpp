
#include <random>
#include <ctime>
#include <d3d11.h>

#include "DXTKGroup.h"
#include "RandomMapMaker.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;


using Microsoft::WRL::ComPtr;
using VT = VertexPositionNormalColor;		//入力レイアウトが位置、色
using PB = PrimitiveBatch<VT>;

//―――――――――――――――――――――――――――――――――
//　静的メンバの実体
//―――――――――――――――――――――――――――――――――

//　カメラ
Camera*								    RandomMapMaker::m_pCamera;



// 立方体の頂点データ
VertexPositionNormalColor vertexes_n[] =
{
	// 正面
	{ Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Red },
	{ Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Yellow },
	{ Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Green },
	{ Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Blue },

	// 右面													  			    
	{ Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::Black },
	{ Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::White },

	// 左面													  			    
	{ Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Purple },
	{ Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Pink },
};


//　頂点インデックス
uint16_t indexes[] =
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


void RandomMapMaker::InitializeStatic(Camera * pCamera)
{
	m_pCamera = pCamera;
}

RandomMapMaker::RandomMapMaker()
{
	srand((unsigned int)time(NULL));

	seedX = 0;
	seedZ = 0;

	width = 30;
	depth = 30;

	MaxHeight = 10;

	relief = 15.0f;

	m_cube.resize(width * depth);

	PolygonInit();

	Initialize();
}

//―――――――――――――――――――――――
//初期化
//
//
//―――――――――――――――――――――――
void RandomMapMaker::Initialize()
{
	seedX = rand() % 100;
	seedZ = rand() % 100;

	//　キューブ生成
	for (int i = 0; i < width*depth; i++)
	{
		Vector3 pos = Vector3(i / width, 0, i % depth);

		//キューブ作成
		m_cube[i].SetTranslation(pos);
		MakeY(i);

		if (m_cube[i].GetTranslation().y >= 2)
		{
			m_cube[i].LoadModel(L"cmo/Grassy.cmo");
		}
		else if (m_cube[i].GetTranslation().y >= 0)
		{
			m_cube[i].LoadModel(L"cmo/Sand.cmo");
		}
		else if (m_cube[i].GetTranslation().y >= -3)
		{
			m_cube[i].LoadModel(L"cmo/Water.cmo");
		}
		else if (m_cube[i].GetTranslation().y >= -5)
		{
			m_cube[i].LoadModel(L"cmo/Stone.cmo");
		}
		
	}
}

//
void RandomMapMaker::PolygonInit()
{
	// DirectXTKの管理オブジェクトの初期化
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	//プリミティブバッチを作成
	primitiveBatch = std::make_unique<PB>(dxtk.m_context);

	//エフェクトを作成
	basicEffect = std::make_unique<BasicEffect>(dxtk.m_device);

	basicEffect->SetVertexColorEnabled(true);

	basicEffect->SetAmbientLightColor(Vector3(0.5f, 0.5f, 1.0f));

	basicEffect->SetLightDiffuseColor(0, Vector3(0.2f, 1.0f, 0.2f));

	basicEffect->SetLightEnabled(0, true);

	basicEffect->SetLightDiffuseColor(0, Vector3(0.2f, 1.0f, 0.2f));

	basicEffect->SetLightDirection(0, Vector3(1.0f, -0.5f, 2.0f));

	basicEffect->SetLightEnabled(1, true);

	basicEffect->SetLightDiffuseColor(1, Vector3(0.5f, 0.2f, 0.3f));

	basicEffect->SetLightDirection(1, Vector3(-1.0f, -0.5f, -2.0f));

	////頂点色を使用するのをエフェクトに教える
	//basicEffect->SetVertexColorEnabled(false);	// 頂点カラー(OFF)
	//basicEffect->SetLightingEnabled(false);		// ライト(ON)
	//basicEffect->SetTextureEnabled(true);		// テクスチャ(OFF)
	//basicEffect->SetPerPixelLighting(false);	// ピクセルライティング(OFF)

	//入力レイアウトを作成する
	//今回使用する頂点シェーダーを所得する
	void const* shaderByteCode;	// プログラムの先頭アドレス

	size_t byteCodeLength;		// プログラムのサイズ

	basicEffect->GetVertexShaderBytecode(
		&shaderByteCode, &byteCodeLength);


	dxtk.m_device->CreateInputLayout(
		VertexPositionNormalColor::InputElements,
		VertexPositionNormalColor::InputElementCount,
		shaderByteCode,
		byteCodeLength,
		inputLayout.GetAddressOf());
}



//―――――――――――――――――――――――
//更新処理
//
//
//―――――――――――――――――――――――
void RandomMapMaker::Update()
{
	m_pCamera->Update();
	m_view = m_pCamera->GetViewMatrix();
	m_proj = m_pCamera->GetProjectionMatrix();
	Calc();
}


//
//
//
void RandomMapMaker::Calc()
{
	for (int i = 0; i < width * depth; i++)
	{
		m_cube[i].Update();
	}
}

//
//
//
//
void RandomMapMaker::MakeY(int number)
{
	//RandomHeighit = rand() % MaxHeight;
	//Vector3 localPos = Vector3(m_cube[number].GetTranslation().x, y, m_cube[number].GetTranslation().z);*/
	//m_cube[number].SetTranslation(localPos);

	

	float xSample = (m_cube[number].GetTranslation().x + seedX) / relief;
	float zSample = (m_cube[number].GetTranslation().z + seedZ) / relief;

	float noise = m_noise.noise(xSample, zSample);

	y = MaxHeight * noise;
	Vector3 localPos = Vector3(m_cube[number].GetTranslation().x, y, m_cube[number].GetTranslation().z);
	m_cube[number].SetTranslation(localPos);
}


//
//
//
//
void RandomMapMaker::Draw()
{
	PolygonDraw();

	// 全箱分描画
	for (int i = 0; i < width * depth; i++)
	{
		//m_cube[i].Draw();
	}
}


//
void RandomMapMaker::PolygonDraw()
{
	// DirectXTKの管理オブジェクトの初期化
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	// ワールド行列、ビュー行列、射影行列を設定
	basicEffect->SetWorld(m_world);
	basicEffect->SetView(m_view);
	basicEffect->SetProjection(m_proj);
	basicEffect->Apply(dxtk.m_context);

	// 深度・ステンシルの設定（通常の設定）
	dxtk.m_context->OMSetDepthStencilState(
		dxtk.m_state->DepthDefault(), 0);

	// ブレンドステートの設定（不透明）
	dxtk.m_context->OMSetBlendState(
		dxtk.m_state->Opaque(), nullptr, 0XFFFFFFFF);

	// カリングの設定（カリングはしない）
	dxtk.m_context->RSSetState(dxtk.m_state->CullCounterClockwise());

	dxtk.m_context->IASetInputLayout(inputLayout.Get());

	// プリミティブの描画
	primitiveBatch->Begin();

	// 三角形リストの描画
	primitiveBatch->DrawIndexed(
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		indexes, 6 * 6, vertexes_n, 4 * 6);

	primitiveBatch->End();
}
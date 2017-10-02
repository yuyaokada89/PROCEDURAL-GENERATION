#include <d3d11.h>

#include "VertexCube.h"
#include "DXTKGroup.h"
#include "MemoryLeakDetector.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;
using VT = VertexPositionNormalColor;		//入力レイアウトが位置、色
using PB = PrimitiveBatch<VT>;


//―――――――――――――――――――――――――――――――――
//　静的メンバの実体
//―――――――――――――――――――――――――――――――――

//　カメラ
Camera*								    VertexCube::m_pCamera;



void VertexCube::InitializeStatic(Camera * pCamera)
{
	m_pCamera = pCamera;
}

VertexCube::VertexCube(Matrix world,XMVECTOR color)
{
	m_world = world;

	m_color = color;

	VertexColorCreate();

	SetUpMemoryLeakDetector();

	PolygonInit();
}

void VertexCube::VertexColorCreate()
{
	vex[0] =
	{
		Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f),m_color 	//0
	};
	vex[1] =
	{
		Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f),m_color 	//1
	};
	vex[2] =
	{
		Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f) ,m_color 	//2
	};
	vex[3] =
	{
		Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,m_color 	//3
	};
	vex[4] =
	{
		Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,m_color 	//4
	};
	vex[5] =
	{
		Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,m_color 	//5
	};
	vex[6] =
	{
		Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,m_color 	//6
	};
	vex[7] =
	{
		Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,m_color 	//7
	};
}

void VertexCube::PolygonInit()
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


void VertexCube::Update()
{
	m_pCamera->Update();
	m_view = m_pCamera->GetViewMatrix();
	m_proj = m_pCamera->GetProjectionMatrix();
}

void VertexCube::Render()
{
	PolygonDraw();
}


void VertexCube::PolygonDraw()
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
		m_indexes, 6 * 6, vex, 4 * 6);
	primitiveBatch->End();
	
}
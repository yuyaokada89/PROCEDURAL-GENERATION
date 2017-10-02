#include <d3d11.h>

#include "VertexCube.h"
#include "DXTKGroup.h"

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


// 立方体の頂点データ
VertexPositionNormalColor vertexes_g[] =
{
	// 正面
	{ Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//0
	{ Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//1
	{ Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//2
	{ Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//3

	// 右面													  			    
	{ Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::LightGreen },	//4
	{ Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::LightGreen },	//5

	// 左面													  			    
	{ Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//6
	{ Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightGreen },	//7
};

// 立方体の頂点データ
VertexPositionNormalColor vertexes_st[] =
{
	// 正面
	{ Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//0
	{ Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//1
	{ Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//2
	{ Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//3

																					// 右面													  			    
	{ Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::Silver },	//4
	{ Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::Silver },	//5

																					// 左面													  			    
	{ Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//6
	{ Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Silver },	//7
};

// 立方体の頂点データ
VertexPositionNormalColor vertexes_w[] =
{
	// 正面
	{ Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//0
	{ Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//1
	{ Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//2
	{ Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//3

																					// 右面													  			    
	{ Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::LightSkyBlue },	//4
	{ Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::LightSkyBlue },	//5

																					// 左面													  			    
	{ Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//6
	{ Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::LightSkyBlue },	//7
};


// 立方体の頂点データ
VertexPositionNormalColor vertexes_sa[] =
{
	// 正面
	{ Vector3(-0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//0
	{ Vector3(-0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//1
	{ Vector3(+0.5f,+1.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//2
	{ Vector3(+0.5f,-0.0f,+0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//3

																						// 右面													  			    
	{ Vector3(+0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::Brown },	//4
	{ Vector3(+0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f) ,Colors::Brown },	//5

																					// 左面													  			    
	{ Vector3(-0.5f,+1.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//6
	{ Vector3(-0.5f,-0.0f,-0.5f),Vector3(0.0f, 0.0f,+1.0f)  ,Colors::Brown },	//7
};

//　頂点インデックス
uint16_t indexes_g[] =
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

//　頂点インデックス
uint16_t indexes_sa[] =
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

//　頂点インデックス
uint16_t indexes_w[] =
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

//　頂点インデックス
uint16_t indexes_st[] =
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


void VertexCube::InitializeStatic(Camera * pCamera)
{
	m_pCamera = pCamera;
}

VertexCube::VertexCube(Matrix world,int Height_num)
{
	m_world = world;
	m_height_num = Height_num;

	PolygonInit();
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

	switch (m_height_num)
	{
	case 0:
		// プリミティブの描画
		primitiveBatch->Begin();
		// 三角形リストの描画
		primitiveBatch->DrawIndexed(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			indexes_g, 6 * 6, vertexes_g, 4 * 6);
		primitiveBatch->End();
		break;
	case 1:
		// プリミティブの描画
		primitiveBatch->Begin();
		// 三角形リストの描画
		primitiveBatch->DrawIndexed(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			indexes_sa, 6 * 6, vertexes_sa, 4 * 6);
		primitiveBatch->End();
		break;
	case 2:
		// プリミティブの描画
		primitiveBatch->Begin();
		// 三角形リストの描画
		primitiveBatch->DrawIndexed(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			indexes_w, 6 * 6, vertexes_w, 4 * 6);
		primitiveBatch->End();
		break;
	case 3:
		// プリミティブの描画
		primitiveBatch->Begin();
		// 三角形リストの描画
		primitiveBatch->DrawIndexed(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			indexes_st, 6 * 6, vertexes_st, 4 * 6);
		primitiveBatch->End();
		break;
	}

	

	
}
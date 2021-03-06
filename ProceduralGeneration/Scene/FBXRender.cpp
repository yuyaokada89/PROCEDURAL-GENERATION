#include "../pch.h"
#include "FBXRender.h"
#include "VertexRender.h"
#include "../DXTKGroup.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;


SceneBase* FBXRender::m_base = NULL;


SceneBase * FBXRender::GetInstance()
{
	//if (m_base == NULL)
	//{
		m_base = new FBXRender();
	//}
	return m_base;
}

FBXRender::FBXRender()
{
	m_outputWidth = 800;
	m_outputHeight = 600;

	this->Initialize();
}

FBXRender::~FBXRender()
{
	m_map.reset();
	m_camera.reset();
}

void FBXRender::Initialize()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();
	std::make_unique<SpriteBatch>(dxtk.m_context);
	std::make_unique<SpriteFont>(dxtk.m_device, L"myfile.spritefont");

	//　カメラの生成
	m_camera = std::make_unique<FollowCamera>(m_outputWidth, m_outputHeight);

	//　3Dオブジェクトクラスの静的メンバを初期化
	Obj3d::InitializeStatic(
		m_camera.get()
		, dxtk.m_device
		, dxtk.m_context
	);

	m_angle = 0;

	m_map = std::make_unique<RandomMapMaker>(true);

}

void FBXRender::UpdateScene(SceneManager * scene)
{
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();
	auto kb = dxtk.m_keyboard->GetState();
	// キー入力の更新
	dxtk.UpdateInputState();

	//　カメラの更新
	m_camera->Update();
	m_view = m_camera->GetViewMatrix();
	m_proj = m_camera->GetProjectionMatrix();

	//　カメラ上昇
	if (kb.IsKeyDown(Keyboard::Keys::Up))
	{
		// 現在の座標・回転角を取得
		Vector3 trans = m_camera->GetTranslation();
		// 移動ベクトル(Z座標後退)
		Vector3 moveV(0, 0.1f, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// 移動ベクトルを回転する
		moveV = Vector3::TransformNormal(moveV, rotm);
		// 移動
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	// カメラ下降
	if (kb.IsKeyDown(Keyboard::Keys::Down))
	{
		// 現在の座標・回転角を取得
		Vector3 trans = m_camera->GetTranslation();
		// 移動ベクトル(Z座標後退)
		Vector3 moveV(0, -0.1f, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// 移動ベクトルを回転する
		moveV = Vector3::TransformNormal(moveV, rotm);
		// 移動
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//　カメラ右移動
	if (kb.IsKeyDown(Keyboard::Keys::Right))
	{
		// 現在の座標・回転角を取得
		Vector3 trans = m_camera->GetTranslation();
		// 移動ベクトル(Z座標後退)
		Vector3 moveV(0.1f, 0, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// 移動ベクトルを回転する
		moveV = Vector3::TransformNormal(moveV, rotm);
		// 移動
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//　カメラ左移動
	if (kb.IsKeyDown(Keyboard::Keys::Left))
	{
		// 現在の座標・回転角を取得
		Vector3 trans = m_camera->GetTranslation();
		// 移動ベクトル(Z座標後退)
		Vector3 moveV(-0.1f, 0, 0);
		Matrix rotm = Matrix::CreateRotationY(0);
		// 移動ベクトルを回転する
		moveV = Vector3::TransformNormal(moveV, rotm);
		// 移動
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//　カメラ前進
	if (kb.IsKeyDown(Keyboard::Keys::W))
	{
		// 現在の座標・回転角を取得
		Vector3 trans = m_camera->GetTranslation();
		// 移動ベクトル(Z座標後退)
		Vector3 moveV(0, 0, -0.1f);
		Matrix rotm = Matrix::CreateRotationY(0);
		// 移動ベクトルを回転する
		moveV = Vector3::TransformNormal(moveV, rotm);
		// 移動
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	//　カメラ後退
	if (kb.IsKeyDown(Keyboard::Keys::S))
	{
		// 現在の座標・回転角を取得
		Vector3 trans = m_camera->GetTranslation();
		// 移動ベクトル(Z座標後退)
		Vector3 moveV(0, 0, 0.1f);
		Matrix rotm = Matrix::CreateRotationY(0);
		// 移動ベクトルを回転する
		moveV = Vector3::TransformNormal(moveV, rotm);
		// 移動
		trans += moveV;
		m_camera->SetTargetPos(trans);
	}

	const float rotSpeed = 0.5f;

	//　カメラ後退
	if (kb.IsKeyDown(Keyboard::Keys::Q))
	{
		m_angle -= rotSpeed;
		m_camera->SetTargetAngle(XMConvertToRadians(m_angle));
	}

	//　カメラ後退
	if (kb.IsKeyDown(Keyboard::Keys::P))
	{
		m_angle += rotSpeed;
		m_camera->SetTargetAngle(XMConvertToRadians(m_angle));
	}

	m_map->Update();

	if (kb.IsKeyDown(Keyboard::Keys::Escape))
	{
		ExitGame();
	}

	if (dxtk.m_keyTracker->IsKeyPressed(Keyboard::Keys::Enter))
	{
		/*シーン遷移*/
		scene->Scene(VertexRender::GetInstance());

		Dispose();

	}
}


void FBXRender::RenderScene()
{
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	m_map->Draw();

	dxtk.m_spriteBatch->Begin();
	dxtk.m_spriteFont->DrawString(dxtk.m_spriteBatch.get(), L"FBXRender", XMFLOAT2(0, 0));
	dxtk.m_spriteBatch->End();
}


void FBXRender::Dispose()
{
	if (m_base != NULL)
	{
		delete m_base;
	}
}

// Exit helper
void FBXRender::ExitGame()
{
	PostQuitMessage(0);
}





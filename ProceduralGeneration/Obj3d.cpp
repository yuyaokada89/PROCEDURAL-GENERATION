//
//　3Dオブジェクトのクラス
//

//　ヘッダファイルのインクルード
#include "Obj3d.h"
#include "DXTKGroup.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//―――――――――――――――――――――――――――――――――
//　静的メンバの実体
//―――――――――――――――――――――――――――――――――

//　カメラ
Camera*								    Obj3d::m_pCamera;

/*汎用描画ステート*/
std::unique_ptr<DirectX::CommonStates>  Obj3d::m_states;

//エフェクトファクトリ
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;


//　コンストラクタ
Obj3d::Obj3d()
{
	//　変数の初期化
	m_scale = Vector3(1, 1, 1);

	//　デフォルトではクォータニオンを使わない
	m_UseQuternion = false;
}

Obj3d::~Obj3d()
{
}



void Obj3d::InitializeStatic(Camera * pCamera, 
	Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, 
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext)
{
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	m_pCamera = pCamera;

	m_states = std::make_unique<CommonStates>(dxtk.m_device);
	m_factory = std::make_unique<EffectFactory>(dxtk.m_device);
	m_factory->SetDirectory(L"Resources");
}


void Obj3d::LoadModel(const wchar_t *filename)
{
	DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

	/*モデルの読み込み*/
	m_model = Model::CreateFromCMO(dxtk.m_device, filename, *m_factory);
}

void Obj3d::Update()
{
	//―――――――――――――――――――――――――――――――――
	// 行列を計算する
	//―――――――――――――――――――――――――――――――――
	 
	//　スケーリング行列
	Matrix scalemat = Matrix::CreateScale(m_scale);
	
	//　回転行列
	Matrix rotmat;

	//　回転行列
	if (m_UseQuternion)
	{//　クォータニオンから回転行列を計算する
		rotmat = Matrix::CreateFromQuaternion(m_rotationQ);
	}
	else
	{//　オイラー角から回転行列を計算する
		Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
		Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
		Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);

		rotmat = rotmatZ * rotmatX * rotmatY;
	}
	//　平行移動行列
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//　ワールド行列を合成
	m_world = scalemat * rotmat * transmat;
	
}

void Obj3d::Draw()
{
	//　モデルが存在していれば描画
	if (m_model != nullptr)
	{

		DXTK::DXTKGroup& dxtk = DXTK::DXTKGroup::singleton();

			m_model->Draw(dxtk.m_context,
				*m_states,
				m_world,
				m_pCamera->GetViewMatrix(),
				m_pCamera->GetProjectionMatrix());
	}
}

void Obj3d::Finalize()
{
	m_states.reset();
	m_factory.reset();
	m_model.reset();
}
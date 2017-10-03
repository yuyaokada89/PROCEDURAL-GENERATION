#pragma once

#include "SceneManager.h"
#include <time.h>
#include <d3d11.h>
#include <vector>
#include "SimpleMath.h"
#include "../FollowCamera.h"
#include "../RandomMapMaker.h"


class FBXRender :public SceneBase
{
public:
	static SceneBase* GetInstance();

	/*コンストラクタ*/
	FBXRender();

	~FBXRender();

	/*初期化*/
	void Initialize();
	/*データの更新*/
	void UpdateScene(SceneManager* scene);
	/*描画*/
	void RenderScene();

	static void Dispose();

	// Exit helper
	void ExitGame();

private:
	static SceneBase* m_base;
	//std::unique_ptr<FollowCamera> m_Camera;
	int m_outputWidth;
	int m_outputHeight;

	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//　カメラ
	std::unique_ptr<FollowCamera> m_camera;

	// マップ
	std::unique_ptr<RandomMapMaker> m_map;

	float m_angle;

};

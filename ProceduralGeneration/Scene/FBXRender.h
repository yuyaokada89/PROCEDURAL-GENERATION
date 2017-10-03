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

	/*�R���X�g���N�^*/
	FBXRender();

	~FBXRender();

	/*������*/
	void Initialize();
	/*�f�[�^�̍X�V*/
	void UpdateScene(SceneManager* scene);
	/*�`��*/
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

	//�@�J����
	std::unique_ptr<FollowCamera> m_camera;

	// �}�b�v
	std::unique_ptr<RandomMapMaker> m_map;

	float m_angle;

};

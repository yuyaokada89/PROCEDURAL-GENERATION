#pragma once

#include "SceneManager.h"
#include "SimpleMath.h"


#include <d3d11.h>
#include <Keyboard.h>
#include <SpriteFont.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <PrimitiveBatch.h>
#include <string>

#include "../FollowCamera.h"
#include "../RandomMapMaker.h"

class VertexRender :public  SceneBase
{
public:
	static SceneBase* GetInstance();
	VertexRender();
	~VertexRender();
	/*������*/
	void Initialize();
	/*�f�[�^�̍X�V*/
	void UpdateScene(SceneManager* scene);
	/*�`��*/
	void RenderScene();
	static void Dispose();

private:
	static SceneBase* m_base;

	int m_outputWidth;
	int m_outputHeight;


	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	/*�X�v���C�g*/
	std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_SpriteFont;

	//�@�J����
	std::unique_ptr<FollowCamera> m_camera;

	// �}�b�v
	std::unique_ptr<RandomMapMaker> m_map;

	float m_angle;


};
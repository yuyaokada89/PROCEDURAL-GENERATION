#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Scene(SceneBase* nextScene)
{
	m_base = nextScene;
}

void SceneManager::Update()
{
	m_base->UpdateScene(this);
}

void SceneManager::Render()
{
	m_base->RenderScene();
}

SceneBase::~SceneBase()
{
}

#pragma once

class SceneBase;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	/*シーン変更関数*/
	void Scene(SceneBase* nextScene);
	/*更新関数*/
	void Update();
	/*描画関数*/
	void Render();

private:
	SceneBase* m_base;

};


class SceneBase
{
public:
	virtual ~SceneBase();
	virtual void Initialize() = 0;
	virtual void UpdateScene(SceneManager* scene) = 0;
	virtual void RenderScene() = 0;
};


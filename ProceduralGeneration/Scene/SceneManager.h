#pragma once

class SceneBase;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	/*�V�[���ύX�֐�*/
	void Scene(SceneBase* nextScene);
	/*�X�V�֐�*/
	void Update();
	/*�`��֐�*/
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


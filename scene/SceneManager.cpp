#include "SceneManager.h"

SceneManager::SceneManager()
{
	m_pScene = nullptr;
	Pad::clearLog();
}
SceneManager::~SceneManager()
{
	if (m_pScene)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
}

void SceneManager::change(SceneBase* scene)
{
	if (!scene)	return;

	if (m_pScene)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}

	// シーン切り替え
	m_pScene = scene;
	m_pScene->init();
	Pad::clearLog();
}

void SceneManager::update()
{
	Pad::update();
	SceneBase* scene = m_pScene->update();

	// シーン切り替え
	if (m_pScene != scene)
	{
		if(m_pScene)
		{
			delete m_pScene;
			m_pScene = nullptr;
		}
		m_pScene = scene;
		m_pScene->init();
	}
}

void SceneManager::draw()
{
	m_pScene->draw();
}
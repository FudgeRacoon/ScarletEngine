#include "scarlet/system/SceneManager.hpp"
using namespace scarlet;

SceneManager::ScenesArray SceneManager::scenes;
Scene* SceneManager::activeScene = nullptr;

SceneManager* SceneManager::Get()
{
    static SceneManager* instance = new SceneManager();
    return instance;
}

uint32 SceneManager::GetSceneCount()
{
    return scenes.size();
}
Scene* SceneManager::GetActiveScene()
{
    SCARLET_CORE_ASSERT_LOG(this->activeScene != nullptr, "No active scene set.");

    return activeScene;
}
Scene* SceneManager::GetSceneAt(int buildIndex)
{
    if(buildIndex >= scenes.size())
    {
        Logger::LogError("Scene build index is out of bounds.");
        return nullptr;
    }

    return scenes[buildIndex];
}
Scene* SceneManager::GetSceneByName(std::string name)
{
    for(Scene* scene : scenes)
        if(scene->GetName() == name)
            return scene;

    Logger::LogWarning("Scene does not exist.");
    return nullptr;
}

void SceneManager::SetActiveScene(int buildIndex)
{
    if(buildIndex >= scenes.size())
    {
        Logger::LogError("Scene build index is out of bounds.");
        return;
    }

    Scene* scene = scenes[buildIndex];
    if(scene == activeScene)
    {
        Logger::LogWarning("Scene is already active.");
        return;
    }

    activeScene = scene;
    activeScene->OnEnterRuntime();
}

void SceneManager::UpdateActiveScene()
{
    SCARLET_CORE_ASSERT_LOG(this->activeScene != nullptr, "No active scene to update.");

    activeScene->OnUpdateRuntime();
    activeScene->OnRenderRuntime();
}


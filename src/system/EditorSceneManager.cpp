#include "scarlet/system//EditorSceneManager.hpp"
using namespace scarlet;

EditorSceneManager* EditorSceneManager::Get()
{
    static EditorSceneManager* instance = new EditorSceneManager();
    return instance;
}

void EditorSceneManager::CreateScene(std::string name)
{
    Scene* scene = new Scene(name, scenes.size());
    scenes.push_back(scene);
}
void EditorSceneManager::RemoveScene(int buildIndex)
{
    if(buildIndex >= scenes.size())
    {
        Logger::LogError("Scene build index is out of bounds.");
        return;
    }

    Scene* scene = scenes[buildIndex];
    if(scene == activeScene)
    {
        Logger::LogWarning("Can not remove currently active scene.");
        return;
    }
    
    int counter = 0;
    for(auto it = scenes.begin(); it != scenes.end(); it++)
    {
        if(counter == buildIndex)
        {
            delete *it;
            scenes.erase(it);
            return;
        }

        counter++;
    }   
}

void EditorSceneManager::SetActiveScene(int buildIndex)
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
}

void EditorSceneManager::UpdateActiveScene()
{
    if(this->activeScene == nullptr)
        Logger::LogWarning("No active scene.");

    activeScene->OnRender();
}

void EditorSceneManager::LoadScenes()
{

}
void EditorSceneManager::SaveScenes()
{

}


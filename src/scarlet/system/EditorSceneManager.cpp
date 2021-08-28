#include "scarlet/system//EditorSceneManager.hpp"
using namespace scarlet;

EditorSceneManager::EditorSceneManager()
{
    this->editorCamera = new Camera();

    this->selector = new editor::Selector(
        scarlet::GraphicsContext::GetViewPort().z,
        scarlet::GraphicsContext::GetViewPort().w
    );
    this->cameraController = new editor::CameraController(this->editorCamera);
}

EditorSceneManager* EditorSceneManager::Get()
{
    static EditorSceneManager* instance = new EditorSceneManager();
    return instance;
}

editor::Selector* EditorSceneManager::GetSelector()
{
    return this->selector;
}
editor::CameraController* EditorSceneManager::GetCameraController()
{
    return this->cameraController;
}

void EditorSceneManager::SetActiveScene(int buildIndex)
{
    SCARLET_CORE_ASSERT_LOG(buildIndex < scenes.size(), "Index is out of bounds.");

    Scene* scene = scenes[buildIndex];
    if(scene == activeScene)
    {
        Logger::LogWarning("Scene is already active.");
        return;
    }

    activeScene = scene;
}

void EditorSceneManager::OnResize()
{
    this->selector->OnResize();
    this->cameraController->OnResize();
}

void EditorSceneManager::CreateScene(std::string name)
{
    Scene* scene = new Scene(name, scenes.size());
    scenes.push_back(scene);
}
void EditorSceneManager::RemoveScene(int buildIndex)
{
    SCARLET_CORE_ASSERT_LOG(buildIndex < scenes.size(), "Index is out of bounds.");

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

void EditorSceneManager::UpdateActiveScene()
{
    SCARLET_CORE_ASSERT_LOG(this->activeScene != nullptr, "No active scene to update.");
    
    this->selector->OnMousePress();
    
    this->cameraController->OnMouseDown();
    this->cameraController->OnMouseScroll();

    activeScene->OnRenderEditor(this->editorCamera, this->selector);
}


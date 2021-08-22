#include "scarlet/system//EditorSceneManager.hpp"
using namespace scarlet;

EditorSceneManager* EditorSceneManager::Get()
{
    static EditorSceneManager* instance = new EditorSceneManager();
    return instance;
}

editor::Selector* EditorSceneManager::GetSelector()
{
    return this->selector;
}
editor::GridLines* EditorSceneManager::GetGridLines()
{
    return this->gridlines;
}
editor::CameraController* EditorSceneManager::GetCameraController()
{
    return this->cameraController;
}

void EditorSceneManager::SetCamera(Camera* camera)
{
    this->editorCamera = camera;
}
void EditorSceneManager::SetActiveScene(int buildIndex)
{
    SCARLET_CORE_ASSERT(buildIndex < scenes.size(), "Index is out of bounds.");

    Scene* scene = scenes[buildIndex];
    if(scene == activeScene)
    {
        Logger::LogWarning("Scene is already active.");
        return;
    }

    activeScene = scene;
}

void EditorSceneManager::ActivateSelector()
{
    if(this->selector == nullptr)
        this->selector = new scarlet::editor::Selector(
            scarlet::GraphicsContext::GetViewPort().z,
            scarlet::GraphicsContext::GetViewPort().w
        );
}
void EditorSceneManager::ActivateGridLines()
{
    if(this->gridlines == nullptr)
    {
        SCARLET_CORE_ASSERT(this->editorCamera != nullptr, "Editor Camera is null.");
        this->gridlines = new editor::GridLines(this->editorCamera);
    }
        
}
void EditorSceneManager::ActivateCameraController()
{
    if(this->cameraController == nullptr)
    {
        SCARLET_CORE_ASSERT(this->editorCamera != nullptr, "Editor Camera is null.");
        this->cameraController = new editor::CameraController(this->editorCamera);
    }
}

void EditorSceneManager::CreateScene(std::string name)
{
    Scene* scene = new Scene(name, scenes.size());
    scenes.push_back(scene);
}
void EditorSceneManager::RemoveScene(int buildIndex)
{
    SCARLET_CORE_ASSERT(buildIndex < scenes.size(), "Index is out of bounds.");

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
    SCARLET_CORE_ASSERT(this->activeScene != nullptr, "No active scene to update.");
    
    this->cameraController->OnMouseDown();
    this->cameraController->OnMouseScroll();

    this->selector->OnMousePress();

    GraphicsContext::GetRenderTarget()->Bind();

    this->gridlines->OnRender();

    GraphicsContext::GetRenderTarget()->UnBind();

    activeScene->OnRenderEditor(this->editorCamera, this->selector);
}

void EditorSceneManager::LoadScenes()
{

}
void EditorSceneManager::SaveScenes()
{

}


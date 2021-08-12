#ifndef EDITORSCENEMANAGER_HPP
#define EDITORSCENEMANAGER_HPP

#include <string>
#include <vector>

#include "scarlet/core/Scene.hpp"

#include "scarlet/debug/Assert.hpp"

#include "scarlet/utils/Logger.hpp"

#include "scarlet/system/SceneManager.hpp"

#include "scarlet/graphics/camera/Camera.hpp"

#include "scarletEditor/GridLines.hpp"
#include "scarletEditor/Selector.hpp"
#include "scarletEditor/CameraController.hpp"

namespace scarlet
{
    class EditorSceneManager : public SceneManager
    {
    private:
        Camera* editorCamera = nullptr;

    private:
        editor::Selector* selector = nullptr;
        editor::GridLines* gridlines = nullptr;
        editor::CameraController* cameraController = nullptr;

    private:
        EditorSceneManager() = default;
        EditorSceneManager(const EditorSceneManager& editorSceneManager) = delete;

    public:
        static EditorSceneManager* Get();

    public:
        void SetCamera(Camera* camera);
        void SetActiveScene(int buildIndex) override;

    public:
        void ActivateSelector();
        void ActivateGridLines();        
        void ActivateCameraController();

    public:
        void CreateScene(std::string name);
        void RemoveScene(int buildInxex);

    public:
        void UpdateActiveScene() override;
    
    public:
        void LoadScenes();
        void SaveScenes();
    };
}

#endif
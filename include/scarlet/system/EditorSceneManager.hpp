#ifndef EDITORSCENEMANAGER_HPP
#define EDITORSCENEMANAGER_HPP

#include <string>
#include <vector>

#include "scarlet/core/debug/Assert.hpp"
#include "scarlet/core/logger/Logger.hpp"

#include "scarlet/scene/Scene.hpp"

#include "scarlet/system/SceneManager.hpp"

#include "scarlet/graphics/camera/Camera.hpp"

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
        editor::CameraController* cameraController = nullptr;

    private:
        EditorSceneManager();
        EditorSceneManager(const EditorSceneManager& editorSceneManager) = delete;

    public:
        static EditorSceneManager* Get();

    public:
        editor::Selector* GetSelector();
        editor::CameraController* GetCameraController();

    public:
        void SetActiveScene(int buildIndex) override;

    public:
        void OnResize();

    public:
        void CreateScene(std::string name);
        void RemoveScene(int buildInxex);

    public:
        void UpdateActiveScene() override;
    };
}

#endif
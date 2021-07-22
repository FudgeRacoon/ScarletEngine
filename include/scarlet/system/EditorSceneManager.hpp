#ifndef EDITORSCENEMANAGER_HPP
#define EDITORSCENEMANAGER_HPP

#include <string>
#include <vector>

#include "scarlet/core/Scene.hpp"

#include "scarlet/utils/Logger.hpp"

#include "scarlet/system/SceneManager.hpp"

#include "scarlet/graphics/Shader.hpp"

#include "scarlet/graphics/camera/Camera.hpp"

namespace scarlet
{
    class EditorSceneManager : public SceneManager
    {
    private:
        EditorSceneManager() = default;
        EditorSceneManager(const EditorSceneManager& editorSceneManager) = delete;

    public:
        static EditorSceneManager* Get();

    public:
        void CreateScene(std::string name);
        void RemoveScene(int buildInxex);

    public:
        void SetActiveScene(int buildIndex) override;        

    public:
        void UpdateActiveScene() override;
    
    public:
        void LoadScenes();
        void SaveScenes();
    };
}

#endif
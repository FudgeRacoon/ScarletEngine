#ifndef EDITORSCENEMANAGER_HPP
#define EDITORSCENEMANAGER_HPP

#include <string>
#include <vector>

#include "core/Scene.hpp"
#include "core/Logger.hpp"

#include "core/manager/SceneManager.hpp"

#include "core/renderer/Shader.hpp"

#include "core/Camera.hpp"

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
        void UpdateActiveScene(Camera*& camera, Shader*& shader) override;
    
    public:
        void LoadScenes();
        void SaveScenes();
    };
}

#endif
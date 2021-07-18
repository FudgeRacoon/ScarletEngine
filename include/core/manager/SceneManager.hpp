#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "core/Scene.hpp"

#include "core/math/Math.hpp"

#include "core/renderer/Shader.hpp"

#include "core/Camera.hpp"

namespace scarlet
{
    class SceneManager
    {
    using ScenesArray = std::vector<Scene*>;

    protected:
        SceneManager() = default;
        SceneManager(const SceneManager& sceneManager) = delete;

    protected:
        static ScenesArray scenes;
        static Scene* activeScene;

    public:
        static SceneManager* Get();

    public:
        uint32 GetSceneCount();
        Scene* GetActiveScene();
        Scene* GetSceneAt(int buildIndex);
        Scene* GetSceneByName(std::string name);

    public:
        virtual void SetActiveScene(int buildIndex);

    public:
        virtual void UpdateActiveScene(Camera*& camera, Shader*& shader);
    };
}

#endif
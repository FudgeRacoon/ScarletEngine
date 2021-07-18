#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

#include "core/manager/GameObjectManager.hpp"

#include "core/math/Math.hpp"

#include "core/renderer/Shader.hpp"

#include "core/GameObject.hpp"
#include "core/Camera.hpp"

namespace scarlet
{   
    class SceneManager;
    class EditorSceneManager;

    class Scene
    {
    private:
        std::string name;
        uint32 buildIndex;

    private:
        GameObjectManager* gameObjectManager;

    private:
        Scene(std::string name, uint32 buildIndex);
        ~Scene();

    public:
        std::string GetName();
        void SetName(std::string name);

    public:
        uint32 GetBuildIndex();
        void SetBuildIndex(uint32 buildIndex);

    private:
        void OnEnter();
        void OnUpdate();
        void OnRender(Camera*& camera, Shader*& shader);

    public:
        GameObject* AddGameObject();
        GameObject* GetGameObject(std::string name);
        void DestroyGameObject(std::string name);

    public:
        template <typename T>
        std::vector<GameObject*> GetGameObjectsOfType()
        {
            return this->gameObjectManager->GetGameObjectsOfType<T>();
        }
    
    friend SceneManager;
    friend EditorSceneManager;
    };
}

#endif
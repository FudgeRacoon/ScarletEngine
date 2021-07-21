#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

#include "scarlet/system/GameObjectManager.hpp"

#include "scarlet/math/Math.hpp"

#include "scarlet/graphics/Shader.hpp"
#include "scarlet/graphics/camera/Camera.hpp"

#include "scarlet/entity/GameObject.hpp"

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
        uint32 GetBuildIndex();
        
    public:
        void SetName(std::string name);
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
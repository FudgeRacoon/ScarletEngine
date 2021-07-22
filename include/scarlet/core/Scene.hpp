#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

#include "scarlet/entity/GameObject.hpp"

#include "scarlet/system/GameObjectManager.hpp"

#include "scarlet/math/Math.hpp"

#include "scarlet/graphics/Shader.hpp"
#include "scarlet/graphics/camera/Camera.hpp"


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
        Camera* sceneCamera;

    private:
        Scene(std::string name, uint32 buildIndex);
        ~Scene();

    public:
        std::string GetName();
        uint32 GetBuildIndex();
        Camera* GetCamera();
        
    public:
        void SetName(std::string name);
        void SetBuildIndex(uint32 buildIndex);
        void SetCamera(Camera* camera);

    private:
        void OnEnter();
        void OnUpdate();
        void OnRender();

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
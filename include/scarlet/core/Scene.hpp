#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

#include "scarlet/common/Types.hpp"

#include "scarlet/entity/Registry.hpp"
#include "scarlet/entity/GameObject.hpp"
#include "scarlet/entity/Transform.hpp"
#include "scarlet/entity/SpriteRenderer.hpp"

#include "scarlet/system/AssetPool.hpp"

#include "scarlet/graphics/Renderer.hpp"
#include "scarlet/graphics/camera/Camera.hpp"

#include "scarletEditor/Selector.hpp"

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
        Registry* registry;

    private:
        Camera* sceneCamera;

    private:
        Scene(std::string name, uint32 buildIndex);
        ~Scene();

    public:
        std::string GetName();
        uint32 GetBuildIndex();
        uint32 GetEntityCount();
        Camera* GetCamera();
        
    public:
        void SetName(std::string name);
        void SetBuildIndex(uint32 buildIndex);
        void SetCamera(Camera* camera);

    private:
        void OnEnterRuntime();
        void OnUpdateRuntime();

    private:
        void OnRenderRuntime();
        void OnRenderEditor(Camera* editorCamera, editor::Selector* editorSelector);

    public:
        GameObject* AddEntity();

    public:
        GameObject* GetEntityById(uint32 id);
        GameObject* GetEntityByName(std::string name);
        template <typename T> std::vector<GameObject*> GetEntitiesOfType()
        {
            return this->registry->GetEntitiesOfType<T>();
        }

    public:
        void DestroyEntityById(uint32 id);
        void DestroyEntityByName(std::string name);
    
    friend SceneManager;
    friend EditorSceneManager;
    };
}

#endif
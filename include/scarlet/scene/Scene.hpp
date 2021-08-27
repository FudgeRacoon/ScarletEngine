#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

#include "scarlet/core/Types.hpp"

#include "scarlet/scene/Registry.hpp"
#include "scarlet/scene/GameObject.hpp"
#include "scarlet/scene/components/Transform.hpp"
#include "scarlet/scene/components/SpriteRenderer.hpp"

#include "scarlet/system/AssetManager.hpp"

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
        uint32 GetEntityCount();
        Registry::EntityTreeMap GetEntities();
        GameObject* GetEntityById(uint32 id);
        GameObject* GetEntityByName(std::string name);

    public:
        template <typename T> 
        std::vector<GameObject*> GetEntitiesOfType()
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
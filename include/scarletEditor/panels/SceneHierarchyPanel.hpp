#ifndef SCENEHIERARCHYPANEL_HPP
#define SCENEHIERARCHYPANEL_HPP

#include <string>
#include <utility>

#include "scarlet/imgui/ImGuiPanel.hpp"

#include "scarlet/input/InputManager.hpp"

#include "scarlet/system/EditorSceneManager.hpp"

#include "scarlet/scene/Registry.hpp"
#include "scarlet/scene/GameObject.hpp"
#include "scarlet/scene/components/Tag.hpp"


namespace scarlet
{
    class SceneHierarchyPanel : public ImGuiPanel
    {
    private:
        GameObject* selectedContext;

    public:
        SceneHierarchyPanel();

    public:
        GameObject* GetSelectedContext();

    private:
        void DrawEntityNode(GameObject* entity);

    private:
        void OnUpdate() override;
    };
}

#endif
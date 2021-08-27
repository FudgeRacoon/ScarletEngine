#ifndef COMPONENTUI_HPP
#define COMPONENTUI_HPP

#include <string>

#include "scarlet/imgui/ImGuiManager.hpp"

#include "scarletEditor/panels/SceneHierarchyPanel.hpp"

namespace scarlet
{
    class InspectorPanel;

    class ComponentUI
    {
    protected:
        std::string title;

    protected:
        bool active;

    public:
        ComponentUI(std::string title);
        virtual ~ComponentUI();

    protected:        
        virtual void OnCheck() = 0;
        virtual void OnUpdate() = 0;

    friend InspectorPanel;
    };
}

#endif
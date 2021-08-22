#ifndef INSPECTOR_WINDOW_HPP
#define INSPECTOR_WINDOW_HPP

#include <vector>

#include "scarlet/imgui/ImGuiManager.hpp"

#include "scarletEditor/panels/ComponentMenu.hpp"
#include "scarletEditor/panels/TransformMenu.hpp"
#include "scarletEditor/panels/SpriteRendererMenu.hpp"

namespace scarlet
{
    class InspectorWindow : public ImGuiPanel
    {
    private:
        std::vector<ComponentMenu*> componentMenus;
    
    public:
        InspectorWindow();
        ~InspectorWindow();

    public:
        ComponentMenu* GetComponentMenu(std::string title);

    public:
        void OnUpdate() override;
    };
}

#endif
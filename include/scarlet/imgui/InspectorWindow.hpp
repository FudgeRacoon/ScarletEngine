#ifndef INSPECTOR_WINDOW_HPP
#define INSPECTOR_WINDOW_HPP

#include <vector>

#include "scarlet/imgui/ImGuiManager.hpp"
#include "scarlet/imgui/ComponentMenu.hpp"
#include "scarlet/imgui/TransformMenu.hpp"
#include "scarlet/imgui/SpriteRendererMenu.hpp"

namespace scarlet
{
    class InspectorWindow : public ImGuiWindow
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
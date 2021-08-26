#ifndef INSPECTOR_WINDOW_HPP
#define INSPECTOR_WINDOW_HPP

#include <vector>

#include "scarlet/imgui/ImGuiManager.hpp"

#include "scarletEditor/panels/components/ComponentUI.hpp"
#include "scarletEditor/panels/components/TransformUI.hpp"
#include "scarletEditor/panels/components/SpriteRendererMenu.hpp"

namespace scarlet
{
    class InspectorPanel : public ImGuiPanel
    {
    private:
        std::vector<ComponentUI*> components;
    
    public:
        InspectorPanel();
        ~InspectorPanel();

    public:
        ComponentUI* GetComponentUI(std::string title);

    public:
        void OnUpdate() override;
    };
}

#endif
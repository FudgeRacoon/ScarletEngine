#ifndef INSPECTOR_WINDOW_HPP
#define INSPECTOR_WINDOW_HPP

#include <vector>

#include "core/layers/ImGuiLayer.hpp"

namespace scarlet
{
    class IComponentMenu;

    class InspectorWindow : public ImGuiWindow
    {
    private:
        std::vector<IComponentMenu*> componentMenus;
    
    public:
        InspectorWindow() : ImGuiWindow("Inspector") {}

    public:
        void Update() override
        {
            ImGui::Begin(this->title.c_str());                         

            ImGui::ShowDemoWindow();

            // for(IComponentMenu* componentMenu : componentMenus)
            // {
            //     // if(componentMenu->IsActive())
            //     //     componentMenu->Update();
            // }
            
            ImGui::End();
        }
    };
}

#endif
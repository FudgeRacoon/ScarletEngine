#ifndef INSPECTOR_WINDOW_HPP
#define INSPECTOR_WINDOW_HPP

#include <map>
#include <string>

#include "core/layers/ImGuiLayer.hpp"
#include "core/layers/IComponentMenu.hpp"

namespace scarlet
{
    class InspectorWindow : public ImGuiWindow
    {
    private:
        std::map<std::string, IComponentMenu*> componentMenus;
    
    public:
        InspectorWindow() : ImGuiWindow("Inspector") {}

    public:
        IComponentMenu* AddComponentMenu(IComponentMenu* componentMenu)
        {
            this->componentMenus.insert(std::make_pair(componentMenu->GetTitle(), componentMenu));
            return componentMenu;
        }
        void RemoveComponentMenu(std::string title)
        {
            std::map<std::string, IComponentMenu*>::iterator it;

            it = componentMenus.find(title);
            if(it == componentMenus.end())
            {
                Logger::LogError("No imgui component menu exists with that name.");
                return;
            }

            componentMenus.erase(it);
            delete it->second;
        }

    public:
        void OnUpdate() override
        {
            ImGui::Begin(this->title.c_str()); 
                
            for(std::pair<std::string, IComponentMenu*> componentMenu : componentMenus)
            {
                if(componentMenu.second->GetActive())
                    componentMenu.second->Update();
            }
            
            ImGui::End();
        }
    };
}

#endif
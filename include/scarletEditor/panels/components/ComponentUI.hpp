#ifndef COMPONENTUI_HPP
#define COMPONENTUI_HPP

#include <string>

namespace scarlet
{
    class InspectorPanel;

    class ComponentUI
    {
    protected:
        std::string title;
        bool active;

    public:
        ComponentUI(std::string title);
        virtual ~ComponentUI();

    protected:        
        virtual void OnUpdate() = 0;

    friend InspectorPanel;
    };
}

#endif
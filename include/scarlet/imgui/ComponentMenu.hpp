#ifndef COMPONENTMENU_HPP
#define COMPONENTMENU_HPP

#include <string>

namespace scarlet
{
    class InspectorWindow;

    class ComponentMenu
    {
    protected:
        std::string title;
        bool active;

    protected:
        const float START_POS = 10.0f;
        const float SPACING = 150.0f;

    public:
        ComponentMenu(std::string title);
        virtual ~ComponentMenu();

    public:
        std::string GetTitle();
        bool GetActive();
        
    public:
        void SetTitle(std::string title);
        void SetActive(bool value);
    
    protected:
        virtual void Update() = 0;

    friend InspectorWindow;
    };
}

#endif
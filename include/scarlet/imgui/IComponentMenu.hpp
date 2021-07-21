#ifndef ICOMPONENTMENU_HPP
#define ICOMPONENTMENU_HPP

#include <string>

namespace scarlet
{
    class IComponentMenu
    {
    protected:
        std::string title;
        bool active;

    public:
        virtual void Update() = 0;

    public:
        std::string GetTitle()
        {
            return this->title;
        }
        void SetTitle(std::string title)
        {
            this->title = title;
        }

    public:
        bool GetActive()
        {
            return this->active;
        }
        void SetActive(bool value)
        {
            this->active = value;
        }
    };
}

#endif
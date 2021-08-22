#ifndef IMGUIPANEL_HPP
#define IMGUIPANEL_HPP

#include <string>

namespace scarlet
{
    class ImGuiPanel
    {
    protected:
        std::string title;

    public:
        ImGuiPanel(std::string title);
        virtual ~ImGuiPanel();

    public:
        std::string GetTitle();
        
    public:
        void SetTitle(std::string title);

    public:
        virtual void OnUpdate() = 0;
    };
}

#endif
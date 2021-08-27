#ifndef IMGUIPANEL_HPP
#define IMGUIPANEL_HPP

#include <string>

#include "imgui/imgui.h"

namespace scarlet
{
    class ImGuiManager;

    class ImGuiPanel
    {
    protected:
        std::string title;

    public:
        ImGuiPanel(std::string title);
        virtual ~ImGuiPanel();

    protected:
        virtual void OnUpdate() = 0;

    friend ImGuiManager;
    };
}

#endif
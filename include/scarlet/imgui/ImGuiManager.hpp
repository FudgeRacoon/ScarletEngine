#ifndef IMGUIMANAGER_HPP
#define IMGUIMANAGER_HPP

#include <map>
#include <string>

#include "SDL2/SDL.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "scarlet/core/Window.hpp"

#include "scarlet/imgui/ImGuiPanel.hpp"

#include "scarlet/utils/logger/Logger.hpp"

namespace scarlet
{
    class ImGuiManager
    {
    private:
        static std::map<std::string, ImGuiPanel*> ImGuiPanels;

    public:
        static void OnInit();
        static void OnEvent(SDL_Event* event);
        static void OnRender();
        static void OnShutDown();

    public:
        static ImGuiPanel* AddPanel(ImGuiPanel* panel);
        static ImGuiPanel* GetPanel(std::string title);
        static void RemovePanel(std::string title);
    };
}

#endif
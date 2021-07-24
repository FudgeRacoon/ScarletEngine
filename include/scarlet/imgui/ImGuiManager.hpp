#ifndef IMGUIMANAGER_HPP
#define IMGUIMANAGER_HPP

#include <map>
#include <string>

#include "SDL2/SDL.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "scarlet/core/Window.hpp"
#include "scarlet/utils/Logger.hpp"

namespace scarlet
{
    class ImGuiWindow
    {
    protected:
        std::string title;

    protected:
        ImGuiWindow(std::string title);

    public:
        virtual void OnUpdate() = 0;

    public:
        std::string GetTitle()
        {
            return this->title;
        }
        void SetTitle(std::string title)
        {
            this->title = title;
        }
    };

    class ImGuiManager
    {
    private:
        static std::map<std::string, ImGuiWindow*> imguiWindows;

    public:
        static void OnAttach();
        static void OnEvent(SDL_Event* event);
        static void OnDetach();

    public:
        static ImGuiWindow* AddWindow(ImGuiWindow* window);
        static void RemoveWindow(std::string title);

    public:
        static void OnRender();
    };
}

#endif
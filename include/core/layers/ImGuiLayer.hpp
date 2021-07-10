#ifndef IMGUILAYER_HPP
#define IMGUILAYER_HPP

#include <map>
#include <string>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "core/Window.hpp"
#include "core/Logger.hpp"

#include "core/manager/InputManager.hpp"

namespace scarlet
{
    class ImGuiWindow
    {
    protected:
        std::string title;

    public:
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

    class ImGuiLayer
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
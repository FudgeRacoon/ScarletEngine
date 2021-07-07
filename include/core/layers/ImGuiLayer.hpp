#ifndef IMGUILAYER_HPP
#define IMGUILAYER_HPP

#include <map>
#include <string>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_sdl.h"
#include "Imgui/imgui_impl_opengl3.h"

#include "core/Window.hpp"
#include "core/Logger.hpp"

namespace scarlet
{
    class ImGuiWindow
    {
    public:
        std::string title;

    public:
        ImGuiWindow(std::string title);

    public:
        virtual void Update() = 0;
    };

    class ImGuiLayer
    {
    private:
        static std::map<std::string, ImGuiWindow*> imguiWindows;

    public:
        static void Init();
        static void Release();

    public:
        static ImGuiWindow* AddWindow(ImGuiWindow* window);
        static void RemoveWindow(std::string title);

    public:
        static void Render();
    };
}

#endif
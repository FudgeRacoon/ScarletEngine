#ifndef PROFILERWINDOW_HPP
#define PROFILERWINDOW_HPP

#include "scarlet/system/EditorSceneManager.hpp"
#include "scarlet/system/AssetPool.hpp"

#include "scarlet/utils/Time.hpp"

#include "scarlet/imgui/ImGuiManager.hpp"

namespace scarlet
{
    class ProfilerWindow : public ImGuiWindow
    {
    public:
        ProfilerWindow() : ImGuiWindow("Profiler") {}

    public:
        void OnUpdate() override
        {
            ImGui::Begin(this->title.c_str());

            ImGui::SetWindowSize(ImVec2(150.0f, 100.0f));

            ImGui::Text("%s", "FrameRate: ");
            ImGui::SameLine();
            ImGui::Text("%.2f", Time::GetFrameRate());

            ImGui::Text("%s", "DeltaTime: ");
            ImGui::SameLine();
            ImGui::Text("%.2fms", Time::GetDeltaTime());

            ImGui::Text("%s", "Entity Count: ");
            ImGui::SameLine();
            ImGui::Text("%d", EditorSceneManager::Get()->GetActiveScene()->GetGameObjectCount());

            ImGui::End();
        }
    };
}

#endif
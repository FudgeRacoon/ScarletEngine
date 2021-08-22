#include "scarlet/imgui/ImGuiPanel.hpp"
using namespace scarlet;

ImGuiPanel::ImGuiPanel(std::string title)
{
    this->title = title;
}
ImGuiPanel::~ImGuiPanel()
{
    
}

std::string ImGuiPanel::GetTitle()
{
    return this->title;
}

void ImGuiPanel::SetTitle(std::string title)
{
    this->title = title;
}
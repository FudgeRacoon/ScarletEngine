#include "scarletEditor/panels/ViewportPanel.hpp"
using namespace scarlet;

ViewportPanel::ViewportPanel() : ImGuiPanel("Viewport") {}

void ViewportPanel::OnUpdate()
{
    ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::Begin(this->title.c_str(), nullptr, ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar);

    ImVec2 viewportPanelSize = ImGui::GetWindowSize();
    Vector4 viewportSize = GraphicsContext::GetViewPort();

    if(viewportSize.z != viewportPanelSize.x || viewportSize.w != viewportPanelSize.y)
    {
        GraphicsContext::SetViewPort(0, 0, viewportPanelSize.x, viewportPanelSize.y);
        GraphicsContext::GetRenderTarget()->Resize(viewportPanelSize.x, viewportPanelSize.y);
        EditorSceneManager::Get()->GetCameraController()->OnResize();
    }
    
    uint32 renderTargetId = GraphicsContext::GetRenderTarget()->GetColorAttachmentId();
    ImGui::Image((void*)renderTargetId, ImVec2(viewportPanelSize.x, viewportPanelSize.y), ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();

    ImGui::PopStyleVar();
}
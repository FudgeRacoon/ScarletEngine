#ifndef TransformUI_HPP
#define TransformUI_HPP

#include <string>

#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"

#include "scarlet/core/math/Math.hpp"
#include "scarlet/core/math/Vector3.hpp"

#include "scarlet/imgui/ImGuiManager.hpp"

#include "scarlet/scene/GameObject.hpp"
#include "scarlet/scene/components/Transform.hpp"

#include "scarletEditor/panels/SceneHierarchyPanel.hpp"
#include "scarletEditor/panels/components/ComponentUI.hpp"

namespace scarlet
{
    class TransformUI : public ComponentUI
    {
    private:
        Transform* transformComponent;
        SceneHierarchyPanel* hierarchyPanel;

    public:
        TransformUI();
        
    private:
        void AddVerticalSpacing(float height);
        void DrawVector3Control(std::string label, Vector3& value, float resetValue = 0.0f, float columnWidth = 125.0f);

    private:
        void OnCheck() override;
        void OnUpdate() override;
    };
}   

#endif
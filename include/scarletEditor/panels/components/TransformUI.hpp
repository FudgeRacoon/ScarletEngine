#ifndef TransformUI_HPP
#define TransformUI_HPP

#include "Imgui/imgui.h"

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
        float* position;

    private:
        Transform* transformComponent;
        SceneHierarchyPanel* hierarchyPanel;

    public:
        TransformUI();
        ~TransformUI();

    private:
        void DrawPositionField();
        void DrawRotationField();
        void DrawScaleField();

    private:
        void OnCheck() override;
        void OnUpdate() override;
    };
}   

#endif
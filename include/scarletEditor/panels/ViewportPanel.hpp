#ifndef VIEWPORTPANEL_HPP
#define VIEWPORTPANEL_HPP

#include "imgui/imgui.h"

#include "scarlet/common/Types.hpp"

#include "scarlet/graphics/GraphicsContext.hpp"

#include "scarlet/imgui/ImGuiPanel.hpp"

#include "scarlet/math/Vector4.hpp"

#include "scarlet/system/EditorSceneManager.hpp"

#include "scarlet/utils/logger/Logger.hpp"

namespace scarlet
{
    class ViewportPanel : public ImGuiPanel
    {
    public:
        ViewportPanel();

    public:
        void OnUpdate() override;
    };
}

#endif
#ifndef VIEWPORTPANEL_HPP
#define VIEWPORTPANEL_HPP

#include "imgui/imgui.h"

#include "scarlet/core/Types.hpp"
#include "scarlet/core/logger/Logger.hpp"
#include "scarlet/core/math/Vector4.hpp"

#include "scarlet/graphics/GraphicsContext.hpp"

#include "scarlet/imgui/ImGuiPanel.hpp"

#include "scarlet/system/EditorSceneManager.hpp"

namespace scarlet
{
    class ViewportPanel : public ImGuiPanel
    {
    public:
        ViewportPanel();

    private:
        void OnUpdate() override;
    };
}

#endif
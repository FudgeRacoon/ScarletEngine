#ifndef TAGUI_HPP
#define TAGUI_HPP

#include <string>

#include "scarlet/imgui/ImGuiManager.hpp"

#include "scarlet/input/InputManager.hpp"

#include "scarlet/utils/MemoryUtils.hpp"

#include "scarlet/scene/GameObject.hpp"
#include "scarlet/scene/components/Tag.hpp"

#include "scarletEditor/panels/SceneHierarchyPanel.hpp"
#include "scarletEditor/panels/components/ComponentUI.hpp"

namespace scarlet
{
    class TagUI : public ComponentUI
    {
    private:
        char* buffer;
        const size bufferSize = 256;

    private:
        Tag* tagComponent;
        SceneHierarchyPanel* hierarchyPanel;

    public:
        TagUI();
        ~TagUI();

    private:
        void DrawTextControl(std::string label, char* buffer, size bytes, float columnWidth = 125.0f);

    private:
        void OnCheck() override;
        void OnUpdate() override;
    };
}

#endif
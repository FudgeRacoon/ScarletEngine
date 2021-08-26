#ifndef TransformUI_HPP
#define TransformUI_HPP

#include "Imgui/imgui.h"

#include "scarletEditor/panels/components/ComponentUI.hpp"

namespace scarlet
{
    class TransformUI : public ComponentUI
    {
    public:
        float* position;
        float* rotation;
        float* scale;

    public:
        TransformUI();
        ~TransformUI();

    private:
        void DrawPositionField();
        void DrawRotationField();
        void DrawScaleField();

    public:
        void OnUpdate() override;
    };
}   

#endif